#!/usr/bin/env node
/**
 * generate-manifest.js
 * -------------------------------------------------------
 * 自动扫描 docs/ 目录，根据文件夹和 .md 文件结构
 * 生成 manifest.json，无需手动维护导航配置。
 *
 * 用法：
 *   node generate-manifest.js
 *
 * 规则：
 *   - docs/ 根目录下的 .md 文件 → isTop 独立链接（按文件名排序）
 *   - docs/ 子目录 → 分组，目录名作为 title（可在下方 FOLDER_NAMES 自定义中文名）
 *   - 子目录内的 .md 文件 → 分组子页面
 *   - 文件排序：优先 index.md / README.md / welcome.md，其余按字母
 *   - 页面 title：取 .md 文件第一行 # 标题，没有则用文件名
 * -------------------------------------------------------
 */

const fs   = require("fs");
const path = require("path");

/* ---- 可配置项 ---- */
const DOCS_DIR   = path.join(__dirname, "docs");
const OUTPUT     = path.join(__dirname, "manifest.json");
const SITE_TITLE = "Mindustry Logic Script Wiki";
const LOGO_TEXT  = "MLS Wiki";

/** 文件夹名 → 显示名（中文）映射，未配置的文件夹将自动首字母大写 */
const FOLDER_NAMES = {
  "getting-started": "快速开始",
  "guide":           "使用指南",
  "reference":       "参考文档",
  "advanced":        "高级用法",
};

/* ---- 工具函数 ---- */

/** 从 .md 文件中提取第一个 # 标题，否则返回 null */
function extractTitle(filePath) {
  try {
    const content = fs.readFileSync(filePath, "utf8");
    const match   = content.match(/^#\s+(.+)$/m);
    return match ? match[1].trim() : null;
  } catch {
    return null;
  }
}

/** 文件名 → 页面 id（去掉 .md 后缀，转为小写，空格换连字符） */
function fileToId(folder, filename) {
  const base = filename.replace(/\.md$/i, "").toLowerCase().replace(/\s+/g, "-");
  return folder ? `${folder}/${base}` : base;
}

/** 文件名 → 显示 title（提取 MD 标题，否则美化文件名） */
function fileToTitle(filePath, filename) {
  const fromMd = extractTitle(filePath);
  if (fromMd) return fromMd;
  return filename
    .replace(/\.md$/i, "")
    .replace(/[-_]/g, " ")
    .replace(/\b\w/g, c => c.toUpperCase());
}

/** 排序：index/readme/welcome 优先，其余按字母 */
function sortFiles(files) {
  const priority = ["index.md", "readme.md", "welcome.md"];
  return files.sort((a, b) => {
    const ai = priority.indexOf(a.toLowerCase());
    const bi = priority.indexOf(b.toLowerCase());
    if (ai !== -1 && bi !== -1) return ai - bi;
    if (ai !== -1) return -1;
    if (bi !== -1) return 1;
    return a.localeCompare(b);
  });
}

/** 文件夹名 → 显示名 */
function folderTitle(name) {
  return FOLDER_NAMES[name] ||
    name.replace(/[-_]/g, " ").replace(/\b\w/g, c => c.toUpperCase());
}

/* ---- 主扫描逻辑 ---- */
function scan() {
  if (!fs.existsSync(DOCS_DIR)) {
    console.error(`[generate-manifest] 找不到 docs/ 目录：${DOCS_DIR}`);
    process.exit(1);
  }

  const entries = fs.readdirSync(DOCS_DIR, { withFileTypes: true });

  // 根目录 .md 文件 → isTop 独立链接
  const rootFiles = sortFiles(
    entries.filter(e => e.isFile() && e.name.endsWith(".md")).map(e => e.name)
  );

  // 子目录 → 分组
  const folders = entries
    .filter(e => e.isDirectory())
    .map(e => e.name)
    .sort();

  const nav = [];

  // 根目录文件
  for (const file of rootFiles) {
    const filePath = path.join(DOCS_DIR, file);
    nav.push({
      id:    fileToId("", file),
      title: fileToTitle(filePath, file),
      file:  `docs/${file}`,
      isTop: true,
    });
  }

  // 子目录分组
  for (const folder of folders) {
    const folderPath = path.join(DOCS_DIR, folder);
    const mdFiles    = sortFiles(
      fs.readdirSync(folderPath).filter(f => f.endsWith(".md"))
    );
    if (mdFiles.length === 0) continue;

    nav.push({
      id:       folder,
      title:    folderTitle(folder),
      children: mdFiles.map(file => {
        const filePath = path.join(folderPath, file);
        return {
          id:    fileToId(folder, file),
          title: fileToTitle(filePath, file),
          file:  `docs/${folder}/${file}`,
        };
      }),
    });
  }

  return nav;
}

/* ---- 写出 manifest.json ---- */
const nav = scan();
const manifest = {
  site: { title: SITE_TITLE, logoText: LOGO_TEXT },
  nav,
};

fs.writeFileSync(OUTPUT, JSON.stringify(manifest, null, 2), "utf8");

console.log(`[generate-manifest] 已生成 manifest.json`);
console.log(`  根目录文件: ${nav.filter(n => n.isTop).length} 个`);
console.log(`  分组:       ${nav.filter(n => n.children).length} 个`);
const total = nav.reduce((s, n) => s + (n.children ? n.children.length : 1), 0);
console.log(`  总文档数:   ${total} 篇`);
