# 安装与配置

## 本地运行

由于浏览器安全策略（CORS），直接双击 `index.html` 打开时 `fetch()` 无法读取本地 `.md` 文件。推荐使用任意本地静态服务器：

```bash
# 方法一：Python（无需安装）
python3 -m http.server 8080

# 方法二：Node.js（全局安装 serve）
npx serve .

# 方法三：VS Code 插件 Live Server
# 安装 "Live Server" 插件后右键 index.html → Open with Live Server
```

然后在浏览器访问 `http://localhost:8080`。

## 部署到 GitHub Pages

### 1. 上传仓库

将整个 `wiki/` 目录（含 `index.html`）推送到 GitHub 仓库的任意分支。

### 2. 配置 Pages

进入仓库 **Settings → Pages**：

- **Source**：选择你的分支（如 `main`）
- **Folder**：若 `index.html` 在仓库根目录选 `/ (root)`，若在 `wiki/` 子目录选 `/wiki`

### 3. 访问

保存后约 1 分钟，访问 `https://<用户名>.github.io/<仓库名>/`。

## 目录结构

```
wiki/
├── index.html          # 唯一 HTML 入口
├── css/
│   ├── base.css        # CSS 变量 & Reset
│   ├── layout.css      # 整体布局
│   ├── sidebar.css     # 树状导航
│   └── markdown.css    # 文档排版
├── js/
│   ├── config.js       # 站点配置 & 文档树（你主要修改这里）
│   ├── markdown.js     # Markdown 解析 & TOC 提取
│   ├── search.js       # 全文搜索引擎
│   └── app.js          # 应用主逻辑
└── docs/               # 所有 .md 文档
    ├── welcome.md
    ├── getting-started/
    ├── guide/
    └── reference/
```

## 自定义站点名称

打开 `js/config.js`，修改顶部的 `SITE` 对象：

```js
const SITE = {
  title: "我的知识库",   // 显示在顶栏
  logoText: "Wiki",
};
```
