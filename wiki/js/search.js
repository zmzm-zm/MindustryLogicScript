/**
 * search.js
 * -------------------------------------------------------
 * 客户端全文搜索：
 *   1. buildIndex()  — 预加载所有 MD 文件，建立搜索索引
 *   2. query(term)   — 对索引做关键词匹配，返回带高亮摘要的结果
 * -------------------------------------------------------
 */

const Search = (() => {

  /** @type {Array<{id, title, text, file}>} */
  let index = [];
  let ready = false;

  /* ---- 扁平化 NAV_TREE 拿到所有叶节点 ---- */
  function flattenDocs(tree) {
    const docs = [];
    function walk(nodes) {
      for (const node of nodes) {
        if (node.file) docs.push({ id: node.id, title: node.title, file: node.file });
        if (node.children) walk(node.children);
      }
    }
    walk(tree);
    return docs;
  }

  /* ---- 构建索引（并行 fetch 所有 MD 文件） ---- */
  async function buildIndex(tree) {
    const docs   = flattenDocs(tree);
    const chunks = await Promise.allSettled(
      docs.map(doc =>
        fetch(doc.file)
          .then(r => r.ok ? r.text() : "")
          .then(text => ({
            id:    doc.id,
            title: doc.title,
            file:  doc.file,
            // 去掉 Markdown 语法符号，只保留纯文本
            text:  stripMarkdown(text),
          }))
          .catch(() => null)
      )
    );

    index = chunks
      .filter(r => r.status === "fulfilled" && r.value)
      .map(r => r.value);

    ready = true;
    return index.length;
  }

  /* ---- 去除 Markdown 符号 ---- */
  function stripMarkdown(md) {
    return md
      .replace(/```[\s\S]*?```/g, " ")   // 代码块
      .replace(/`[^`]+`/g, " ")           // 行内代码
      .replace(/\[([^\]]+)\]\([^)]*\)/g, "$1") // 链接
      .replace(/[#*_~>|]/g, " ")          // 特殊字符
      .replace(/\s+/g, " ")
      .trim();
  }

  /**
   * 查询
   * @param  {string} term
   * @returns {Array<{id, title, excerpt, score}>}
   */
  function query(term) {
    if (!ready || !term.trim()) return [];

    const kw = term.trim().toLowerCase();

    const results = [];
    for (const doc of index) {
      const titleLower = doc.title.toLowerCase();
      const textLower  = doc.text.toLowerCase();

      let score = 0;
      if (titleLower.includes(kw)) score += 10;
      if (textLower.includes(kw))  score += 1;
      if (score === 0) continue;

      results.push({
        id:      doc.id,
        title:   doc.title,
        excerpt: buildExcerpt(doc.text, kw, 120),
        score,
      });
    }

    // 按分数排序
    results.sort((a, b) => b.score - a.score);
    return results.slice(0, 8);
  }

  /**
   * 从文本中截取含关键词的摘要，并用 <mark> 高亮
   */
  function buildExcerpt(text, kw, maxLen) {
    const lower = text.toLowerCase();
    const pos   = lower.indexOf(kw);
    if (pos === -1) {
      return escape(text.slice(0, maxLen)) + "…";
    }

    const start  = Math.max(0, pos - 40);
    const end    = Math.min(text.length, pos + kw.length + 80);
    let   snippet= text.slice(start, end);
    if (start > 0)  snippet = "…" + snippet;
    if (end < text.length) snippet += "…";

    // 高亮所有出现位置（忽略大小写）
    const re = new RegExp(escapeRe(kw), "gi");
    return escape(snippet).replace(
      new RegExp(escapeRe(escape(kw)), "gi"),
      m => `<mark>${m}</mark>`
    );
  }

  function escape(str) {
    return str
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;");
  }

  function escapeRe(str) {
    return str.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
  }

  return { buildIndex, query, isReady: () => ready };
})();
