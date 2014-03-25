<html><head>
<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  <title>hello.c</title>
</head>
<body bgcolor="#ffffff" text="#000000">
<pre><font color="#444444">/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi &lt;miklos@szeredi.hu&gt;

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/</font>

<font color="0000ff"><strong>#define FUSE_USE_VERSION 26</strong></font>

<font color="0000ff"><strong>#include <font color="#008000">&lt;fuse.h&gt;</font></strong></font>
<font color="0000ff"><strong>#include <font color="#008000">&lt;stdio.h&gt;</font></strong></font>
<font color="0000ff"><strong>#include <font color="#008000">&lt;string.h&gt;</font></strong></font>
<font color="0000ff"><strong>#include <font color="#008000">&lt;errno.h&gt;</font></strong></font>
<font color="0000ff"><strong>#include <font color="#008000">&lt;fcntl.h&gt;</font></strong></font>

<strong>static</strong> <strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">hello_str</font> <font color="4444FF">=</font> <font color="#008000">"Hello World!<font color="#77dd77">\n</font>"</font><font color="4444FF">;</font>
<strong>static</strong> <strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">hello_path</font> <font color="4444FF">=</font> <font color="#008000">"/hello"</font><font color="4444FF">;</font>

<strong>static</strong> <strong>int</strong> <font color="#2040a0">hello_getattr</font><font color="4444FF">(</font><strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">path</font>, <strong>struct</strong> <font color="#2040a0">stat</font> <font color="4444FF">*</font><font color="#2040a0">stbuf</font><font color="4444FF">)</font>
<font color="4444FF"><strong>{</strong></font>
	<strong>int</strong> <font color="#2040a0">res</font> <font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">;</font>

	<font color="#2040a0">memset</font><font color="4444FF">(</font><font color="#2040a0">stbuf</font>, <font color="#FF0000">0</font>, <strong>sizeof</strong><font color="4444FF">(</font><strong>struct</strong> <font color="#2040a0">stat</font><font color="4444FF">)</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">strcmp</font><font color="4444FF">(</font><font color="#2040a0">path</font>, <font color="#008000">"/"</font><font color="4444FF">)</font> <font color="4444FF">=</font><font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">)</font> <font color="4444FF"><strong>{</strong></font>
		<font color="#2040a0">stbuf</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">st_mode</font> <font color="4444FF">=</font> <font color="#2040a0">S_IFDIR</font> <font color="4444FF">|</font> <font color="#FF0000">0755</font><font color="4444FF">;</font>
		<font color="#2040a0">stbuf</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">st_nlink</font> <font color="4444FF">=</font> <font color="#FF0000">2</font><font color="4444FF">;</font>
	<font color="4444FF"><strong>}</strong></font> <strong>else</strong> <strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">strcmp</font><font color="4444FF">(</font><font color="#2040a0">path</font>, <font color="#2040a0">hello_path</font><font color="4444FF">)</font> <font color="4444FF">=</font><font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">)</font> <font color="4444FF"><strong>{</strong></font>
		<font color="#2040a0">stbuf</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">st_mode</font> <font color="4444FF">=</font> <font color="#2040a0">S_IFREG</font> <font color="4444FF">|</font> <font color="#FF0000">0444</font><font color="4444FF">;</font>
		<font color="#2040a0">stbuf</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">st_nlink</font> <font color="4444FF">=</font> <font color="#FF0000">1</font><font color="4444FF">;</font>
		<font color="#2040a0">stbuf</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">st_size</font> <font color="4444FF">=</font> <font color="#2040a0">strlen</font><font color="4444FF">(</font><font color="#2040a0">hello_str</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<font color="4444FF"><strong>}</strong></font> <strong>else</strong>
		<font color="#2040a0">res</font> <font color="4444FF">=</font> <font color="4444FF">-</font><font color="#2040a0">ENOENT</font><font color="4444FF">;</font>

	<strong>return</strong> <font color="#2040a0">res</font><font color="4444FF">;</font>
<font color="4444FF"><strong>}</strong></font>

<strong>static</strong> <strong>int</strong> <font color="#2040a0">hello_readdir</font><font color="4444FF">(</font><strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">path</font>, <strong>void</strong> <font color="4444FF">*</font><font color="#2040a0">buf</font>, <font color="#2040a0">fuse_fill_dir_t</font> <font color="#2040a0">filler</font>,
			 <font color="#2040a0">off_t</font> <font color="#2040a0">offset</font>, <strong>struct</strong> <font color="#2040a0">fuse_file_info</font> <font color="4444FF">*</font><font color="#2040a0">fi</font><font color="4444FF">)</font>
<font color="4444FF"><strong>{</strong></font>
	<font color="4444FF">(</font><strong>void</strong><font color="4444FF">)</font> <font color="#2040a0">offset</font><font color="4444FF">;</font>
	<font color="4444FF">(</font><strong>void</strong><font color="4444FF">)</font> <font color="#2040a0">fi</font><font color="4444FF">;</font>

	<strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">strcmp</font><font color="4444FF">(</font><font color="#2040a0">path</font>, <font color="#008000">"/"</font><font color="4444FF">)</font> <font color="4444FF">!</font><font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">)</font>
		<strong>return</strong> <font color="4444FF">-</font><font color="#2040a0">ENOENT</font><font color="4444FF">;</font>

	<font color="#2040a0">filler</font><font color="4444FF">(</font><font color="#2040a0">buf</font>, <font color="#008000">"."</font>, <font color="#2040a0">NULL</font>, <font color="#FF0000">0</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<font color="#2040a0">filler</font><font color="4444FF">(</font><font color="#2040a0">buf</font>, <font color="#008000">".."</font>, <font color="#2040a0">NULL</font>, <font color="#FF0000">0</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<font color="#2040a0">filler</font><font color="4444FF">(</font><font color="#2040a0">buf</font>, <font color="#2040a0">hello_path</font> <font color="4444FF">+</font> <font color="#FF0000">1</font>, <font color="#2040a0">NULL</font>, <font color="#FF0000">0</font><font color="4444FF">)</font><font color="4444FF">;</font>

	<strong>return</strong> <font color="#FF0000">0</font><font color="4444FF">;</font>
<font color="4444FF"><strong>}</strong></font>

<strong>static</strong> <strong>int</strong> <font color="#2040a0">hello_open</font><font color="4444FF">(</font><strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">path</font>, <strong>struct</strong> <font color="#2040a0">fuse_file_info</font> <font color="4444FF">*</font><font color="#2040a0">fi</font><font color="4444FF">)</font>
<font color="4444FF"><strong>{</strong></font>
	<strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">strcmp</font><font color="4444FF">(</font><font color="#2040a0">path</font>, <font color="#2040a0">hello_path</font><font color="4444FF">)</font> <font color="4444FF">!</font><font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">)</font>
		<strong>return</strong> <font color="4444FF">-</font><font color="#2040a0">ENOENT</font><font color="4444FF">;</font>

	<strong>if</strong> <font color="4444FF">(</font><font color="4444FF">(</font><font color="#2040a0">fi</font><font color="4444FF">-</font><font color="4444FF">&gt;</font><font color="#2040a0">flags</font> <font color="4444FF">&amp;</font> <font color="#FF0000">3</font><font color="4444FF">)</font> <font color="4444FF">!</font><font color="4444FF">=</font> <font color="#2040a0">O_RDONLY</font><font color="4444FF">)</font>
		<strong>return</strong> <font color="4444FF">-</font><font color="#2040a0">EACCES</font><font color="4444FF">;</font>

	<strong>return</strong> <font color="#FF0000">0</font><font color="4444FF">;</font>
<font color="4444FF"><strong>}</strong></font>

<strong>static</strong> <strong>int</strong> <font color="#2040a0">hello_read</font><font color="4444FF">(</font><strong>const</strong> <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">path</font>, <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">buf</font>, <font color="#2040a0">size_t</font> <font color="#2040a0">size</font>, <font color="#2040a0">off_t</font> <font color="#2040a0">offset</font>,
		      <strong>struct</strong> <font color="#2040a0">fuse_file_info</font> <font color="4444FF">*</font><font color="#2040a0">fi</font><font color="4444FF">)</font>
<font color="4444FF"><strong>{</strong></font>
	<font color="#2040a0">size_t</font> <font color="#2040a0">len</font><font color="4444FF">;</font>
	<font color="4444FF">(</font><strong>void</strong><font color="4444FF">)</font> <font color="#2040a0">fi</font><font color="4444FF">;</font>
	<strong>if</strong><font color="4444FF">(</font><font color="#2040a0">strcmp</font><font color="4444FF">(</font><font color="#2040a0">path</font>, <font color="#2040a0">hello_path</font><font color="4444FF">)</font> <font color="4444FF">!</font><font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">)</font>
		<strong>return</strong> <font color="4444FF">-</font><font color="#2040a0">ENOENT</font><font color="4444FF">;</font>

	<font color="#2040a0">len</font> <font color="4444FF">=</font> <font color="#2040a0">strlen</font><font color="4444FF">(</font><font color="#2040a0">hello_str</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">offset</font> <font color="4444FF">&lt;</font> <font color="#2040a0">len</font><font color="4444FF">)</font> <font color="4444FF"><strong>{</strong></font>
		<strong>if</strong> <font color="4444FF">(</font><font color="#2040a0">offset</font> <font color="4444FF">+</font> <font color="#2040a0">size</font> <font color="4444FF">&gt;</font> <font color="#2040a0">len</font><font color="4444FF">)</font>
			<font color="#2040a0">size</font> <font color="4444FF">=</font> <font color="#2040a0">len</font> <font color="4444FF">-</font> <font color="#2040a0">offset</font><font color="4444FF">;</font>
		<font color="#2040a0">memcpy</font><font color="4444FF">(</font><font color="#2040a0">buf</font>, <font color="#2040a0">hello_str</font> <font color="4444FF">+</font> <font color="#2040a0">offset</font>, <font color="#2040a0">size</font><font color="4444FF">)</font><font color="4444FF">;</font>
	<font color="4444FF"><strong>}</strong></font> <strong>else</strong>
		<font color="#2040a0">size</font> <font color="4444FF">=</font> <font color="#FF0000">0</font><font color="4444FF">;</font>

	<strong>return</strong> <font color="#2040a0">size</font><font color="4444FF">;</font>
<font color="4444FF"><strong>}</strong></font>

<strong>static</strong> <strong>struct</strong> <font color="#2040a0">fuse_operations</font> <font color="#2040a0">hello_oper</font> <font color="4444FF">=</font> <font color="4444FF"><strong>{</strong></font>
	.<font color="#2040a0">getattr</font>	<font color="4444FF">=</font> <font color="#2040a0">hello_getattr</font>,
	.<font color="#2040a0">readdir</font>	<font color="4444FF">=</font> <font color="#2040a0">hello_readdir</font>,
	.<font color="#2040a0">open</font>		<font color="4444FF">=</font> <font color="#2040a0">hello_open</font>,
	.<font color="#2040a0">read</font>		<font color="4444FF">=</font> <font color="#2040a0">hello_read</font>,
<font color="4444FF"><strong>}</strong></font><font color="4444FF">;</font>

<strong>int</strong> <font color="#2040a0">main</font><font color="4444FF">(</font><strong>int</strong> <font color="#2040a0">argc</font>, <strong>char</strong> <font color="4444FF">*</font><font color="#2040a0">argv</font><font color="4444FF">[</font><font color="4444FF">]</font><font color="4444FF">)</font>
<font color="4444FF"><strong>{</strong></font>
	<strong>return</strong> <font color="#2040a0">fuse_main</font><font color="4444FF">(</font><font color="#2040a0">argc</font>, <font color="#2040a0">argv</font>, <font color="4444FF">&amp;</font><font color="#2040a0">hello_oper</font>, <font color="#2040a0">NULL</font><font color="4444FF">)</font><font color="4444FF">;</font>
<font color="4444FF"><strong>}</strong></font>

</pre>
<hr>
syntax highlighted by <a href="http://www.palfrader.org/code2html">Code2HTML</a>, v. 0.9.1


</body></html>
