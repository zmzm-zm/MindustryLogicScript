# 简介

本知识库是一个**零依赖**的纯静态 Wiki，除了 `marked.js`（通过 CDN 加载）之外，不依赖任何第三方框架或构建工具。

## 设计目标

### 轻量

整个站点由 4 个 CSS 文件、4 个 JS 文件和 1 个 HTML 文件构成，压缩后总体积不超过 50 KB。

### 易于维护

文档以 `.md` 文件独立存放，结构清晰，方便多人协作。目录树通过 `js/config.js` 集中管理，新增文档只需两步：

1. 创建 `.md` 文件
2. 在 `config.js` 的 `NAV_TREE` 中注册

### 可定制

颜色、字体、间距均通过 CSS 变量控制，修改 `css/base.css` 中的 `:root` 变量即可全局生效。

## 技术栈

| 模块 | 实现方式 |
|------|----------|
| Markdown 解析 | marked.js v9（CDN） |
| 路由 | Hash 路由（`#page=id`） |
| 搜索 | 客户端全文索引 |
| 主题 | CSS 自定义属性 + `data-theme` |
| 代码高亮 | 可选接入 highlight.js |

## 浏览器兼容性

支持所有现代浏览器（Chrome / Firefox / Safari / Edge 最新版）。不支持 IE。
