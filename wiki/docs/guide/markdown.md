# Markdown 语法

本站使用 [marked.js](https://marked.js.org/) 解析 Markdown，完整支持 GFM（GitHub Flavored Markdown）。

## 标题

```md
# H1 一级标题
## H2 二级标题（会显示在 TOC 中）
### H3 三级标题（缩进显示在 TOC）
#### H4 四级标题
```

> H2 ~ H4 标题会自动提取到右侧"本页目录"，鼠标悬停标题还会出现 `#` 锚链接。

## 段落与强调

这是普通段落文字。**粗体** 用两个星号，*斜体* 用一个星号，~~删除线~~ 用两个波浪号，`行内代码` 用反引号。

## 列表

无序列表：

- 苹果
- 香蕉
  - 大香蕉
  - 小香蕉
- 葡萄

有序列表：

1. 第一步：安装
2. 第二步：配置
3. 第三步：部署

## 链接与图片

```md
[链接文字](https://example.com)
![图片描述](https://picsum.photos/400/200)
```

## 代码块

行内代码：`const x = 1`

围栏代码块（可指定语言）：

```javascript
function greet(name) {
  return `你好，${name}！`;
}

console.log(greet("世界"));
```

```bash
# 启动本地服务器
python3 -m http.server 8080
```

## 引用

> 这是一段引用文字。
> 引用可以多行。
>
> 也可以有多段。

## 表格

| 名称       | 类型     | 默认值  | 说明           |
|------------|----------|---------|----------------|
| `id`       | `string` | —       | 唯一文档标识   |
| `title`    | `string` | —       | 显示名称       |
| `file`     | `string` | —       | MD 文件路径    |
| `children` | `array`  | `[]`    | 子节点列表     |

## 分割线

---

## HTML 支持

marked.js 默认允许在 MD 中嵌入 HTML，但建议尽量使用纯 MD 语法以保持可移植性。
