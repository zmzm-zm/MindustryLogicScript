# 主题定制

所有视觉样式均通过 `css/base.css` 中的 CSS 变量控制。

## 修改颜色

打开 `css/base.css`，找到 `:root`（亮色）和 `[data-theme="dark"]`（暗色）两个规则块，修改对应变量即可。

### 亮色主题变量

```css
:root {
  --color-bg:          #ffffff;   /* 主背景 */
  --color-bg-sidebar:  #f7f7f7;   /* 侧边栏背景 */
  --color-bg-hover:    #efefef;   /* 悬停背景 */
  --color-bg-active:   #e8e8e8;   /* 选中背景 */
  --color-bg-code:     #f0f0f0;   /* 代码块背景 */

  --color-border:      #e5e5e5;   /* 主边框 */
  --color-border-mid:  #d4d4d4;   /* 中等边框 */

  --color-text:        #111111;   /* 主文本 */
  --color-text-muted:  #666666;   /* 次要文本 */
  --color-text-faint:  #999999;   /* 淡文本 */

  --color-accent:      #0070f3;   /* 主题色（链接、高亮） */
  --color-accent-hover:#0060d1;   /* 主题色悬停 */
  --color-accent-soft: #e8f0fe;   /* 主题色浅底 */
}
```

## 修改字体

同样在 `css/base.css` 的 `body` 规则中修改 `font-family`：

```css
body {
  font-family: "你的字体", -apple-system, sans-serif;
}
```

## 修改代码字体

代码块使用 `markdown.css` 中的 `.md-content code` 规则：

```css
.md-content code {
  font-family: "JetBrains Mono", "Fira Code", monospace;
}
```

## 添加代码高亮

如需语法高亮，在 `index.html` 的 `<head>` 中引入 highlight.js：

```html
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/highlight.js@11/styles/github.min.css" />
<script src="https://cdn.jsdelivr.net/npm/highlight.js@11/highlight.min.js"></script>
```

然后在 `js/app.js` 的文档渲染完成后调用：

```js
document.querySelectorAll("pre code").forEach(el => hljs.highlightElement(el));
```
