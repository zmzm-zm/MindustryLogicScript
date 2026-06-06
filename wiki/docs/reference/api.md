# API 说明

本页说明各 JS 模块对外暴露的接口，供二次开发或集成时参考。

## Markdown 模块

文件：`js/markdown.js`，暴露全局对象 `Markdown`。

### `Markdown.init()`

初始化 marked.js 并配置自定义 renderer。**必须在 marked.js 加载后调用一次。**

### `Markdown.parse(mdText)`

将 Markdown 文本解析为 HTML 和 TOC。

```js
const { html, toc } = Markdown.parse(mdText);
// html  — 解析后的 HTML 字符串
// toc   — 标题列表 Array<{ level, text, slug }>
```

### `Markdown.slugify(text)`

将标题文本转换为 URL 友好的 slug：

```js
Markdown.slugify("核心概念 & 设计"); // => "核心概念--设计"
```

---

## Search 模块

文件：`js/search.js`，暴露全局对象 `Search`。

### `Search.buildIndex(tree)`

异步构建搜索索引，会 `fetch` NAV_TREE 中所有 `.md` 文件。返回 `Promise<number>`（已索引的文档数量）。

```js
const count = await Search.buildIndex(NAV_TREE);
console.log(`已索引 ${count} 篇文档`);
```

### `Search.query(term)`

同步查询，返回最多 8 条结果：

```js
const results = Search.query("安装");
// [{ id, title, excerpt, score }, ...]
```

### `Search.isReady()`

返回 `boolean`，索引构建完成后为 `true`。

---

## Router 模块

文件：`js/app.js`，暴露 `Router`。

### `Router.go(id)`

导航到指定文档，更新 URL hash 并加载内容：

```js
Router.go("getting-started/install");
```
