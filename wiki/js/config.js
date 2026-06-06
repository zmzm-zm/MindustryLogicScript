/**
 * config.js
 * -------------------------------------------------------
 * 从 manifest.json 加载站点配置与导航树。
 *
 * 如果你想手动维护导航，直接编辑 manifest.json 即可。
 * 如果你想自动生成，运行：node generate-manifest.js
 * -------------------------------------------------------
 */

const Config = (() => {
  let _nav  = [];
  let _site = {};

  async function load() {
    try {
      const res  = await fetch("manifest.json?_=" + Date.now());
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      const data = await res.json();
      _nav  = data.nav  || [];
      _site = data.site || {};
    } catch (e) {
      console.error("[wiki] manifest.json 加载失败：", e.message);
      // 降级：空导航
      _nav  = [];
      _site = { title: "知识库", logoText: "Wiki" };
    }
  }

  function getNav()  { return _nav;  }
  function getSite() { return _site; }

  return { load, getNav, getSite };
})();
