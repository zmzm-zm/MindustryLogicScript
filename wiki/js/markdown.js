/**
 * markdown.js
 * -------------------------------------------------------
 * 使用 marked.js（CDN）将 Markdown 转为 HTML，
 * 并从 AST 中提取标题树用于页内 TOC。
 * -------------------------------------------------------
 */

const Markdown = (() => {

  /* ---- marked 配置 ---- */
  function configure() {
    // 自定义 renderer：给标题自动添加 id 和锚链接
    const renderer = new marked.Renderer();

    renderer.heading = function (text, level) {
      // marked v9+ 传入对象，兼容旧版字符串
      if (typeof text === "object") {
        level = text.depth;
        text  = text.text;
      }
      const slug = slugify(text);
      const anchor = `<a class="heading-anchor" href="#${slug}" aria-hidden="true">#</a>`;
      return `<h${level} id="${slug}">${text}${anchor}</h${level}>`;
    };

    marked.use({
      renderer,
      gfm: true,
      breaks: false,
      mangle: false,
      headerIds: false,  // 我们自己处理
    });
  }

  /* ---- slug 工具 ---- */
  function slugify(text) {
    return text
      .toLowerCase()
      .replace(/[^\w\u4e00-\u9fa5\s-]/g, "")
      .trim()
      .replace(/[\s]+/g, "-");
  }

  /* ---- 解析 Markdown → { html, toc } ---- */
  function parse(mdText) {
    const toc = extractToc(mdText);
    const html = marked.parse(mdText);
    return { html, toc };
  }

  /**
   * 从 Markdown 文本中提取标题列表，用于构建 TOC。
   * 返回 Array<{ level: 2|3|4, text: string, slug: string }>
   */
  function extractToc(mdText) {
    const toc = [];
    const re = /^(#{1,4})\s+(.+)$/gm;
    let match;
    while ((match = re.exec(mdText)) !== null) {
      const level = match[1].length;
      if (level < 2 || level > 4) continue; // 只收 h2-h4
      const raw   = match[2].trim();
      // 去掉行内 MD 标记（粗体、代码等）
      const text  = raw.replace(/[*_`~[\]()]/g, "");
      toc.push({ level, text, slug: slugify(text) });
    }
    return toc;
  }

  /* ---- 初始化 ---- */
  function init() {
    if (typeof marked === "undefined") {
      console.error("[wiki] marked.js 未加载，Markdown 渲染不可用。");
      return;
    }
    configure();
  }

  return { init, parse, slugify };
})();
