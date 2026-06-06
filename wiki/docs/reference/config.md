# 配置项说明

`js/config.js` 是整个站点的配置文件，包含站点信息和文档树定义。

## SITE 对象

```js
const SITE = {
  title: "我的知识库",   // 显示在顶栏 Logo 旁
  logoText: "Wiki",      // Logo 图标旁的短文字（可选）
};
```

## NAV_TREE 数组

`NAV_TREE` 是一个数组，每个元素描述一个导航节点。

### 顶部独立链接节点

```js
{
  id: "welcome",           // 必填，唯一标识
  title: "首页",            // 必填，侧边栏显示名称
  file: "docs/welcome.md", // 必填，MD 文件路径（相对 index.html）
  isTop: true,             // 标记为顶部独立链接
}
```

### 分组节点

```js
{
  id: "guide",             // 必填，分组唯一标识
  title: "使用指南",        // 必填，分组标题
  children: [              // 必填，子节点数组
    {
      id: "guide/markdown",
      title: "Markdown 语法",
      file: "docs/guide/markdown.md",
    },
    // ...
  ],
}
```

### 节点字段详解

| 字段       | 类型      | 必填 | 说明 |
|------------|-----------|------|------|
| `id`       | `string`  | 是   | 全局唯一，用于 URL hash 和路由匹配 |
| `title`    | `string`  | 是   | 侧边栏显示的名称 |
| `file`     | `string`  | 叶节点必填 | MD 文件路径，相对于 `index.html` |
| `children` | `array`   | 分组必填   | 子节点列表，与 `file` 互斥 |
| `isTop`    | `boolean` | 否   | 为 `true` 时显示在树顶部，不归属任何分组 |

## 路由规则

URL hash 格式为 `#page=<id>`，例如：

```
https://example.com/wiki/#page=getting-started/install
```

首次访问（无 hash）时，自动跳转到 `NAV_TREE` 中第一个带 `file` 字段的节点。
