/**
 * app.js
 * -------------------------------------------------------
 * 应用主逻辑：
 *   - 主题切换
 *   - 左侧侧边栏开关
 *   - 右侧 TOC 面板开关（统一抽屉模式）
 *   - 树状导航渲染
 *   - Hash 路由
 *   - MD 文件加载与渲染
 *   - 页内 TOC 滚动高亮
 *   - 搜索交互
 * -------------------------------------------------------
 */

/* ======================================================
   1. 主题
   ====================================================== */
   const Theme = (() => {
    const KEY = "wiki-theme";

    function get() {
      return localStorage.getItem(KEY) ||
        (window.matchMedia("(prefers-color-scheme: dark)").matches ? "dark" : "light");
    }

     function apply(theme) {
       document.documentElement.setAttribute("data-theme", theme);
       localStorage.setItem(KEY, theme);

       // 切换 highlight.js 主题
       const hljsTheme = document.getElementById("hljs-theme");
       if (hljsTheme) {
         const themeMap = {
           dark: "https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/styles/github-dark.min.css",
           light: "https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/styles/github.min.css"
         };
         hljsTheme.href = themeMap[theme] || themeMap.light;
       }

       const btn = document.getElementById("theme-toggle");
       if (!btn) return;
       btn.querySelector(".icon-sun").style.display = theme === "dark" ? "block" : "none";
       btn.querySelector(".icon-moon").style.display = theme === "light" ? "block" : "none";

       const logoSvg = document.getElementById("logo-svg");
       if (logoSvg) logoSvg.setAttribute("stroke", theme === "dark" ? "#111111" : "white");
     }
  
    function toggle() { apply(get() === "dark" ? "light" : "dark"); }
  
    function init() {
      apply(get());
      document.getElementById("theme-toggle")?.addEventListener("click", toggle);
    }
  
    return { init };
  })();
  
  
  /* ======================================================
     2. 左侧侧边栏开关
     ====================================================== */
  const Sidebar = (() => {
    let collapsed = false;
  
    function init() {
      const sidebar = document.getElementById("sidebar");
      const main    = document.getElementById("main");
      const toggle  = document.getElementById("sidebar-toggle");
  
      toggle?.addEventListener("click", () => {
        collapsed = !collapsed;
        sidebar.classList.toggle("is-collapsed", collapsed);
        main.classList.toggle("sidebar-collapsed", collapsed);
        toggle.querySelector(".icon-chevron-left").style.display  = collapsed ? "none"  : "block";
        toggle.querySelector(".icon-chevron-right").style.display = collapsed ? "block" : "none";
      });
  
      document.getElementById("sidebar-overlay")?.addEventListener("click", closeMobile);
    }
  
    function openMobile() {
      document.getElementById("sidebar")?.classList.add("is-mobile-open");
      document.getElementById("sidebar-overlay")?.classList.add("is-visible");
    }
  
    function closeMobile() {
      document.getElementById("sidebar")?.classList.remove("is-mobile-open");
      document.getElementById("sidebar-overlay")?.classList.remove("is-visible");
    }
  
    return { init, openMobile, closeMobile };
  })();
  
  
  /* ======================================================
     3. 右侧 TOC 面板开关（统一抽屉模式）
     ====================================================== */
  const TocPanel = (() => {
    let isOpen = false;
  
    function setIcons(toggle, open) {
      const closeIcon = toggle.querySelector(".icon-toc-close");
      const openIcon  = toggle.querySelector(".icon-toc-open");
      if (closeIcon) closeIcon.style.display = open ? "flex" : "none";
      if (openIcon)  openIcon.style.display  = open ? "none" : "flex";
    }
  
    function openDrawer(panel, toggle) {
      panel.classList.add("is-open");
      document.getElementById("toc-overlay")?.classList.add("is-visible");
      setIcons(toggle, true);
      isOpen = true;
    }
  
    function closeDrawer(panel, toggle) {
      panel.classList.remove("is-open");
      document.getElementById("toc-overlay")?.classList.remove("is-visible");
      setIcons(toggle, false);
      isOpen = false;
    }
  
    function toggleDrawer() {
      const toggle = document.getElementById("toc-toggle");
      const panel  = document.getElementById("toc-panel");
      if (!toggle || !panel) return;
  
      if (isOpen) {
        closeDrawer(panel, toggle);
      } else {
        openDrawer(panel, toggle);
      }
    }
  
    function close() {
      const toggle = document.getElementById("toc-toggle");
      const panel  = document.getElementById("toc-panel");
      if (panel && toggle && isOpen) {
        closeDrawer(panel, toggle);
      }
    }
  
    function init() {
      const toggle = document.getElementById("toc-toggle");
      const panel  = document.getElementById("toc-panel");
      const overlay = document.getElementById("toc-overlay");
  
      if (!toggle || !panel) return;
  
      // 初始状态：折叠，图标正确
      setIcons(toggle, false);
      isOpen = false;
  
      toggle.addEventListener("click", toggleDrawer);
  
      // 点击遮罩关闭
      overlay?.addEventListener("click", () => close());
  
      // 视口变化时，如果 TOC 处于打开状态，保持打开（只是内容自适应）
      // 不需要额外处理，宽度响应式由 CSS 控制
    }
  
    return { init, close };
  })();
  
  
  /* ======================================================
     4. 树状导航渲染
     ====================================================== */
  const Tree = (() => {
    function render(tree, activeId) {
      const container = document.getElementById("tree-nav");
      if (!container) return;
      container.innerHTML = "";
  
      for (const node of tree) {
        if (node.isTop) {
          const el = document.createElement("div");
          el.className = "tree-top-item" + (node.id === activeId ? " is-active" : "");
          el.dataset.id = node.id;
          el.innerHTML = `${iconDoc()}<span>${node.title}</span>`;
          el.addEventListener("click", () => Router.go(node.id));
          container.appendChild(el);
          continue;
        }
  
        if (node.children) {
          const hasActive = node.children.some(c => c.id === activeId);
          const group = document.createElement("div");
          group.className = "tree-group is-open";
  
          group.innerHTML = `
            <button class="tree-group__header" aria-expanded="true">
              <span>${node.title}</span>
              <span class="tree-group__arrow">${iconChevron()}</span>
            </button>
            <ul class="tree-items">
              ${node.children.map(child => `
                <li class="tree-item${child.id === activeId ? " is-active" : ""}"
                    data-id="${child.id}">
                  ${iconDoc()}
                  <span>${child.title}</span>
                </li>
              `).join("")}
            </ul>
          `;
  
          const header = group.querySelector(".tree-group__header");
          header.addEventListener("click", () => {
            const open = group.classList.toggle("is-open");
            header.setAttribute("aria-expanded", open);
          });
  
          group.querySelectorAll(".tree-item").forEach(item => {
            item.addEventListener("click", () => Router.go(item.dataset.id));
          });
  
          container.appendChild(group);
        }
      }
    }
  
    function iconDoc() {
      return `<span class="tree-item__icon">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2">
          <path stroke-linecap="round" stroke-linejoin="round" d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z"/>
        </svg>
      </span>`;
    }
  
    function iconChevron() {
      return `<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2">
        <path stroke-linecap="round" stroke-linejoin="round" d="M9 5l7 7-7 7"/>
      </svg>`;
    }
  
    return { render };
  })();
  
  
  /* ======================================================
     5. 页内 TOC 滚动高亮
     ====================================================== */
  const Toc = (() => {
    let observer = null;
    let scrollHandler = null;
    let currentToc = [];
  
    function render(toc) {
      const panel = document.getElementById("toc-nav");
      if (!panel) return;
  
      if (!toc || toc.length === 0) {
        panel.innerHTML = "";
        cleanup();
        return;
      }
  
      currentToc = toc;
  
      panel.innerHTML = toc.map(item => `
        <li class="toc-h${item.level}">
          <a href="#${item.slug}" data-slug="${item.slug}">${item.text}</a>
        </li>
      `).join("");
  
      startObserver(toc);
      startScrollTracker(toc);
    }
  
    function cleanup() {
      if (observer) { observer.disconnect(); observer = null; }
      if (scrollHandler) {
        window.removeEventListener("scroll", scrollHandler, { passive: true });
        scrollHandler = null;
      }
    }
  
    function startObserver(toc) {
      if (observer) observer.disconnect();
  
      const links = {};
      document.querySelectorAll("#toc-nav a").forEach(a => {
        links[a.dataset.slug] = a;
      });
  
      observer = new IntersectionObserver(
        entries => {
          for (const e of entries) {
            if (e.isIntersecting) {
              Object.values(links).forEach(a => a.classList.remove("is-active"));
              const a = links[e.target.id];
              if (a) a.classList.add("is-active");
            }
          }
        },
        { rootMargin: "-20% 0px -70% 0px" }
      );
  
      toc.forEach(({ slug }) => {
        const el = document.getElementById(slug);
        if (el) observer.observe(el);
      });
    }
  
    // Scroll-based TOC tracking as a reliable supplement to IntersectionObserver.
    function startScrollTracker(toc) {
      if (scrollHandler) window.removeEventListener("scroll", scrollHandler, { passive: true });
  
      let ticking = false;
      scrollHandler = () => {
        if (ticking) return;
        ticking = true;
        requestAnimationFrame(() => {
          ticking = false;
          highlightByScroll(toc);
        });
      };
  
      window.addEventListener("scroll", scrollHandler, { passive: true });
      highlightByScroll(toc);
    }
  
    function highlightByScroll(toc) {
      const links = {};
      document.querySelectorAll("#toc-nav a").forEach(a => {
        links[a.dataset.slug] = a;
      });
  
      const offset = 100; // top offset for sticky header
      let activeSlug = null;
  
      for (const item of toc) {
        const el = document.getElementById(item.slug);
        if (!el) continue;
        if (el.getBoundingClientRect().top <= offset) {
          activeSlug = item.slug;
        }
      }
  
      Object.values(links).forEach(a => a.classList.remove("is-active"));
      if (activeSlug && links[activeSlug]) {
        links[activeSlug].classList.add("is-active");
      }
    }
  
    return { render };
  })();
  
  
  /* ======================================================
     6. 路由
     ====================================================== */
  const Router = (() => {
    let currentPageId = null;
    let pendingSlug   = null;
  
    function findNode(id, tree) {
      for (const node of tree) {
        if (node.id === id) return node;
        if (node.children) {
          const found = findNode(id, node.children);
          if (found) return found;
        }
      }
      return null;
    }
  
    function firstLeaf(tree) {
      for (const node of tree) {
        if (node.file) return node.id;
        if (node.children) {
          const id = firstLeaf(node.children);
          if (id) return id;
        }
      }
      return null;
    }
  
    function scrollToSlug(slug) {
      if (!slug) return;
      const el = document.getElementById(slug);
      if (!el) return;
      const y = el.getBoundingClientRect().top + window.pageYOffset - 72;
      window.scrollTo({ top: y, behavior: "smooth" });
    }
  
    async function load(id, slug) {
      const nav  = Config.getNav();
      const node = findNode(id, nav);
      if (!node || !node.file) return;
  
      currentPageId = id;
      Tree.render(nav, id);
  
      const group = nav.find(g => g.children?.some(c => c.id === id));
      renderBreadcrumb(group?.title, node.title);
  
      showSkeleton();
  
      try {
        const res = await fetch(node.file + "?_=" + Date.now());
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        const md = await res.text();
        const { html, toc } = Markdown.parse(md);
  
        document.getElementById("md-content").innerHTML = html;
        Toc.render(toc);
  
        if (slug) {
          requestAnimationFrame(() => {
            requestAnimationFrame(() => {
              scrollToSlug(slug);
            });
          });
        } else {
          window.scrollTo(0, 0);
        }
      } catch (e) {
        document.getElementById("md-content").innerHTML = `
          <p style="color:var(--color-text-muted);">文档加载失败：${e.message}</p>
          <p style="color:var(--color-text-faint);font-size:0.85rem;">
            请确认文件 <code>${node.file}</code> 存在。
          </p>`;
        Toc.render([]);
      }
    }
  
    function showSkeleton() {
      const lines = [["60%","28px","12px"], ["90%","14px","8px"], ["80%","14px","8px"],
                     ["85%","14px","28px"], ["45%","20px","12px"], ["88%","14px","8px"], ["75%","14px","0"]];
      document.getElementById("md-content").innerHTML = lines.map(([w,h,mb]) =>
        `<div style="width:${w};height:${h};border-radius:4px;background:var(--color-bg-code);margin-bottom:${mb};"></div>`
      ).join("");
    }
  
    function renderBreadcrumb(group, page) {
      const el = document.getElementById("breadcrumb");
      if (!el) return;
      el.innerHTML = group
        ? `<span>${group}</span><span class="breadcrumb__sep">/</span><span>${page}</span>`
        : `<span>${page}</span>`;
    }
  
    function go(id, slug) {
      if (slug) {
        location.hash = `#page=${id}~${slug}`;
      } else {
        location.hash = `#page=${id}`;
      }
      Sidebar.closeMobile();
      // 导航后关闭 TOC 抽屉
      TocPanel.close();
    }
  
    // Same-page navigation: just scroll, don't reload
    function goToSlug(slug) {
      if (slug && currentPageId) {
        location.hash = `#page=${currentPageId}~${slug}`;
      }
      if (slug) scrollToSlug(slug);
    }
  
    function handleHash() {
      const full  = location.hash;
      const match = full.match(/^#page=([^~]+?)(?:~(.+))?$/);
      const nav   = Config.getNav();
      const id    = match
        ? decodeURIComponent(match[1])
        : firstLeaf(nav) ?? "";
      const slug  = match ? match[2] : null;
  
      if (!id) return;
  
      // Same page — just scroll to the heading, don't reload
      if (id === currentPageId && slug) {
        requestAnimationFrame(() => scrollToSlug(slug));
        return;
      }
      if (id === currentPageId && !slug) return;
  
      load(id, slug);
    }
  
    function init() {
      window.addEventListener("hashchange", handleHash);
  
      // Intercept TOC link clicks
      document.addEventListener("click", e => {
        const tocLink = e.target.closest("#toc-nav a");
        if (tocLink) {
          e.preventDefault();
          const slug = tocLink.dataset.slug;
          if (slug) {
            location.hash = `#page=${currentPageId}~${slug}`;
            scrollToSlug(slug);
            // 点击 TOC 链接后关闭抽屉（移动端/桌面端都更友好）
            TocPanel.close();
          }
          return;
        }
  
        // Heading anchor links in rendered content
        const headingAnchor = e.target.closest(".heading-anchor");
        if (headingAnchor) {
          e.preventDefault();
          const href = headingAnchor.getAttribute("href");
          const slug = href ? href.replace(/^#/, "") : null;
          if (slug) {
            location.hash = `#page=${currentPageId}~${slug}`;
            scrollToSlug(slug);
          }
          return;
        }
      });
  
      handleHash();
    }
  
    return { init, go, goToSlug, scrollToSlug, getCurrentPageId: () => currentPageId };
  })();
  
  
  /* ======================================================
     7. 搜索
     ====================================================== */
  const SearchUI = (() => {
    let debounceTimer = null;
    let focusIndex    = -1;
  
    function init() {
      const input    = document.getElementById("search-input");
      const dropdown = document.getElementById("search-dropdown");
      if (!input || !dropdown) return;
  
      input.addEventListener("input", () => {
        clearTimeout(debounceTimer);
        debounceTimer = setTimeout(() => runSearch(input.value), 200);
      });
  
      input.addEventListener("keydown", e => {
        if (e.key === "ArrowDown")  { e.preventDefault(); moveFocus(1); }
        if (e.key === "ArrowUp")    { e.preventDefault(); moveFocus(-1); }
        if (e.key === "Enter")      { e.preventDefault(); selectFocused(); }
        if (e.key === "Escape")     { close(); input.blur(); }
      });
  
      document.addEventListener("click", e => {
        if (!e.target.closest(".topbar__search")) close();
      });
  
      input.addEventListener("focus", () => {
        if (input.value.trim()) runSearch(input.value);
      });
    }
  
    function runSearch(term) {
      const dropdown = document.getElementById("search-dropdown");
      const results  = Search.query(term);
      focusIndex = -1;
  
      if (!term.trim()) { close(); return; }
  
      if (results.length === 0) {
        dropdown.innerHTML = `<p class="search-empty">未找到与 "<strong>${esc(term)}</strong>" 相关的内容</p>`;
      } else {
        dropdown.innerHTML = results.map((r, i) => `
          <div class="search-result-item" data-index="${i}" data-id="${r.id}" data-slug="${r.slug || ""}">
            <div class="search-result-item__title">${esc(r.title)}</div>
            <div class="search-result-item__excerpt">${r.excerpt}</div>
          </div>
        `).join("");
  
        dropdown.querySelectorAll(".search-result-item").forEach(item => {
          item.addEventListener("mousedown", e => {
            e.preventDefault();
            const id   = item.dataset.id;
            const slug = item.dataset.slug || null;
  
            if (id === Router.getCurrentPageId() && slug) {
              Router.goToSlug(slug);
            } else {
              Router.go(id, slug);
            }
            close();
            document.getElementById("search-input").value = "";
          });
        });
      }
  
      dropdown.classList.add("is-open");
    }
  
    function moveFocus(dir) {
      const items = document.querySelectorAll(".search-result-item");
      if (!items.length) return;
      items[focusIndex]?.classList.remove("is-focused");
      focusIndex = Math.max(0, Math.min(items.length - 1, focusIndex + dir));
      items[focusIndex]?.classList.add("is-focused");
      items[focusIndex]?.scrollIntoView({ block: "nearest" });
    }
  
    function selectFocused() {
      const item = document.querySelector(".search-result-item.is-focused");
      if (item) {
        const id   = item.dataset.id;
        const slug = item.dataset.slug || null;
  
        if (id === Router.getCurrentPageId() && slug) {
          Router.goToSlug(slug);
        } else {
          Router.go(id, slug);
        }
        close();
        document.getElementById("search-input").value = "";
      }
    }
  
    function close() {
      document.getElementById("search-dropdown")?.classList.remove("is-open");
      focusIndex = -1;
    }
  
    function esc(str) {
      return str.replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;");
    }
  
    return { init };
  })();
  
  
  /* ======================================================
     8. 启动
     ====================================================== */
  document.addEventListener("DOMContentLoaded", async () => {
    await Config.load();
  
    const site = Config.getSite();
    if (site.title)    document.title = site.title;
    if (site.logoText) {
      const el = document.getElementById("site-title");
      if (el) el.textContent = site.logoText;
    }
  
    Markdown.init();
    Theme.init();
    Sidebar.init();
    TocPanel.init();
    Router.init();
    SearchUI.init();
  
    Search.buildIndex(Config.getNav());
  
    document.getElementById("mobile-menu-btn")?.addEventListener("click", Sidebar.openMobile);
  });