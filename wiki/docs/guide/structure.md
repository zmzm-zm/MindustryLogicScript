# 目录结构

了解项目文件结构有助于快速定位需要修改的文件。

## 完整结构

```
wiki/
├── index.html              # 入口文件，定义 HTML 骨架并加载资源
│
├── css/                    # 样式层（纯 CSS，无预处理器）
│   ├── base.css            # CSS 变量（颜色/阴影）、Reset、全局基础
│   ├── layout.css          # 顶栏、侧边栏、内容区、TOC 的布局
│   ├── sidebar.css         # 树状导航的交互样式
│   └── markdown.css        # Markdown 内容的排版样式
│
├── js/                     # 逻辑层（原生 ES5/ES6，无框架）
│   ├── config.js           # ★ 站点配置与文档树（日常维护入口）
│   ├── markdown.js         # Markdown 解析、TOC 提取
│   ├── search.js           # 全文搜索索引与查询
│   └── app.js              # 应用主逻辑（路由、渲染、事件绑定）
│
└── docs/                   # 文档内容（纯 Markdown）
    ├── welcome.md          # 首页
    ├── getting-started/
    │   ├── intro.md
    │   ├── install.md
    │   └── usage.md
    ├── guide/
    │   ├── markdown.md
    │   ├── structure.md    # 本文件
    │   └── theme.md
    └── reference/
        ├── api.md
        └── config.md
```

## 日常维护只需关注

### `js/config.js`

新增/删除/排序文档时修改 `NAV_TREE`。该文件是整个站点唯一的"目录清单"。

### `docs/` 目录

放置所有 `.md` 文档，可以任意组织子目录层级，只要 `config.js` 中的 `file` 路径正确即可。

### `css/base.css`

修改颜色、字体时只改这一个文件，通过 CSS 变量全局生效。

## 加载顺序

`index.html` 底部按以下顺序加载脚本，**不可调换**：

```html
<script src="js/config.js"></script>   <!-- 先定义 NAV_TREE 全局变量 -->
<script src="js/markdown.js"></script> <!-- 再加载解析器 -->
<script src="js/search.js"></script>   <!-- 再加载搜索引擎 -->
<script src="js/app.js"></script>      <!-- 最后启动应用 -->
```
