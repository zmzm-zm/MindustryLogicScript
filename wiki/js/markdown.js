const Markdown = (() => {
  function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
  }

  function registerMlsLanguages() {
    if (typeof hljs === 'undefined') return;
    if (hljs.getLanguage('mls')) return;
    try {
      hljs.registerLanguage('mls', function(hljs) {
        return {
          name: 'mls',
          case_insensitive: true,
          keywords: {
            keyword: 'func if elseif else while return var const class new import from :',
            built_in: 'print input len type str int bool float list dict',
            literal: 'true false null undefined'
          },
          contains: [
            {
              className: 'comment',
              begin: '~~',
              end: '~~',
              contains: [hljs.PHRASAL_WORDS_MODE]
            },
            {
              className: 'comment',
              begin: '~',
              end: '\n|~',
              contains: [hljs.PHRASAL_WORDS_MODE]
            },
            hljs.QUOTE_STRING_MODE,
            { className: 'string', begin: "'", end: "'" },
            { className: 'number', begin: '\\b\\d+(\\.\\d+)?\\b', relevance: 0 },
            {
              className: 'function',
              begin: '\\bfunc\\s+([a-zA-Z_][a-zA-Z0-9_]*)',
              end: '\\(',
              contains: [hljs.UNDERSCORE_TITLE_MODE]
            },
            { className: 'operator', begin: '[+\\-*/%=<>!&|]+' }
          ]
        };
      });
    } catch (e) {
      console.error('[markdown] mls注册失败:', e);
    }
  }

  function registerMlLanguages() {
    if (typeof hljs === 'undefined') return;
    if (hljs.getLanguage('ml')) return;

    try {
      hljs.registerLanguage('ml', function(hljs) {
        return {
          name: 'ml',
          case_insensitive: true,
          keywords: {
            keyword: 'set mod print printflush',
            built_in: 'op jump',
            literal: 'true false null undefined'
          },
          contains: [
            {
              className: 'comment',
              begin: '~',
              end: '$',
              contains: [hljs.PHRASAL_WORDS_MODE]
            },
            { className: 'string', begin: '"', end: '"' },
            { className: 'string', begin: "'", end: "'" },
            { className: 'number', begin: '\\b\\d+(\\.\\d+)?\\b', relevance: 0 },
            {
              className: 'operator',
              begin: '[+\\-*/%=<>!&|]+'
            },
            { className: 'keyword', begin: '\\b(op|jump)\\b' },
          ]
        };
      });
    } catch (e) {
      console.error('[markdown] ml注册失败:', e);
    }
  }

  function slugify(text) {
    return text
        .toLowerCase()
        .replace(/[^\w\u4e00-\u9fa5\s-]/g, "")
        .trim()
        .replace(/[\s]+/g, "-");
  }

  function configure() {
    registerMlsLanguages();
    registerMlLanguages();

    const renderer = new marked.Renderer();

    renderer.code = function(token) {
      let code = token.text || token;
      const language = token.lang || '';

      let codeText = typeof code === 'string' ? code : '';
      if (typeof code === 'object' && code !== null) {
        codeText = code.text || code.code || '';
      }

      if (typeof hljs === 'undefined') {
        return `<pre><code class="language-${language || 'plaintext'}">${escapeHtml(codeText)}</code></pre>`;
      }

      const langMap = {
        'c++': 'cpp',
        'cpp': 'cpp',
        'c': 'cpp',
        'mls': 'mls',
        'ml': 'ml'
      };

      const normalizedLang = language ? langMap[language.toLowerCase()] || language : null;
      const finalLang = normalizedLang || 'plaintext';
      const validLang = hljs.getLanguage(finalLang);

      try {
        let highlighted;
        if (validLang) {
          highlighted = hljs.highlight(codeText, { language: finalLang }).value;
        } else {
          highlighted = hljs.highlightAuto(codeText).value;
        }
        return `<pre><code class="hljs language-${finalLang}">${highlighted}</code></pre>`;
      } catch (e) {
        return `<pre><code class="language-${finalLang}">${escapeHtml(codeText)}</code></pre>`;
      }
    };

    renderer.heading = function(text, level) {
      if (typeof text === "object") {
        level = text.depth;
        text = text.text;
      }
      const slug = slugify(text);
      const anchor = `<a class="heading-anchor" href="#${slug}" aria-hidden="true">#</a>`;
      return `<h${level} id="${slug}">${text}${anchor}</h${level}>`;
    };

    marked.use({ renderer });

    marked.setOptions({
      gfm: true,
      breaks: false,
      mangle: false,
      headerIds: false,
    });
  }

  function parse(mdText) {
    const toc = extractToc(mdText);
    const html = marked.parse(mdText);
    return { html, toc };
  }

  function extractToc(mdText) {
    const toc = [];
    const re = /^(#{1,4})\s+(.+)$/gm;
    let match;
    while ((match = re.exec(mdText)) !== null) {
      const level = match[1].length;
      if (level < 2 || level > 4) continue;
      const raw = match[2].trim();
      const text = raw.replace(/[*_`~[\]()]/g, "");
      toc.push({ level, text, slug: slugify(text) });
    }
    return toc;
  }

  function init() {
    if (typeof marked === "undefined") {
      console.error("[wiki] marked.js 未加载");
      return;
    }
    configure();
  }

  if (typeof hljs !== 'undefined') {
    registerMlsLanguages();
  } else {
    document.addEventListener('DOMContentLoaded', registerMlsLanguages);
  }

  return { init, parse, slugify };
})();