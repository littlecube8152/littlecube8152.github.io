---
title: "[internal] markdown feature testing"
date: 1900-01-01T00:00:00+00:00
draft: false
---


## Markdown Extensions

### PHP Markdown Extra: Definition lists (`definitionList`)
[Syntax Documentation](https://michelf.ca/projects/php-markdown/extra/#def-list)

Term 1
Term 2
:   Definition a

Term 3
:   Definition b

Term 4
:   A very long definition that I just made up so the website will actually render this nonsense

Term 5

:   This definition has a code block, a blockquote and a list.

        code block.

    > block quote
    > on two lines.

    1.  first list item
    2.  second list item


### Hugo Goldmark Extensions: Extras (`extras`)
(Not enabled)

~~foo~~
++foo++
==bar==
H~2~O
1^st^

### PHP Markdown Extra: Footnotes (`footnotes`)

That's some text with a footnote.[^1]

[^1]: And that's the footnote.

### GitHub Flavored Markdown: Autolinks (`linkify`)

This website https://gohugo.io should be a link, and default to http, like www.google.com.
This email foo@bar.baz will be rendered!

Not sure why mailto:foo@bar.baz won't work tho

### Hugo Goldmark Extensions: Passthrough (`passthrough`)

This piece of math equation, $a^*=x-b^*$ is typed using `a^*=x-b^*`, in which the pair `*` might be substituted by italics format HTML tag. 

### Goldmark Extensions: Typographer (`typographer`)

These 'single' quote, "double" quote, <<angle>> quote are recognized. 
Also, dashes (as in higher-order terms), en dashes (as in Floyd--Warshall algorithm), and em dashes (this is not --- well it might be) and ellipsis...
they are parsed as well.

