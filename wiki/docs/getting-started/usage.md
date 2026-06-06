# 基本用法

## 新增文档

### 第一步：创建 Markdown 文件

在 `docs/` 目录的合适位置创建 `.md` 文件，例如：

```
docs/guide/deploy.md
```

### 第二步：在 config.js 中注册

打开 `js/config.js`，找到 `NAV_TREE`，在对应分组的 `children` 中添加：

```js
{
  id: "guide/deploy",      // 唯一 ID，建议用路径风格
  title: "部署指南",        // 显示在侧边栏的名称
  file: "docs/guide/deploy.md",  // 相对于 index.html 的路径
},
```

保存后刷新页面，新文档即出现在导航树中。

## 新增分组

在 `NAV_TREE` 中添加一个带 `children` 的对象：

```js
{
  id: "advanced",
  title: "进阶用法",
  children: [
    { id: "advanced/plugin", title: "插件系统", file: "docs/advanced/plugin.md" },
    { id: "advanced/ci",     title: "CI/CD 集成", file: "docs/advanced/ci.md" },
  ],
},
```

## 搜索

顶栏搜索框在页面加载后会自动抓取所有 `.md` 文件并建立索引。

- 输入关键词即可搜索，支持中英文
- 结果按相关度排序，标题匹配权重更高
- 摘要中高亮显示匹配词
- 方向键 `↑` `↓` 导航，`Enter` 跳转，`Esc` 关闭

## 主题切换

点击顶栏右侧的图标即可切换亮色/暗色。偏好会保存到 `localStorage`，下次访问自动恢复。

若未手动设置，默认跟随操作系统的颜色主题（`prefers-color-scheme`）。
