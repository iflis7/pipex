
<h1 align="center">
	📖 pipex
</h1>

<p align="center">
	<b><i>Discover in detail  of UNIX mechanism - `pipe`</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/iflis7/push_swap?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/iflis7/push_swap?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/iflis7/push_swap?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/iflis7/push_swap?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/iflis7/push_swap?color=green" />
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

The purpose of this project is the discovery in detail UNIX mechanism - `pipe`.<br>
You can read the subject: [`pipex.subject.pdf`](subject/pipex.subject.pdf)


### Discription of mandatory part
The program `pipex` should repeat the behaviour of the next shell command
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like this:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
All errors like: wrong commands,  permission to files and etc, need be handle.

### Testers
1) [Pipex Tester](https://github.com/vfurmane/pipex-tester "Pipex tester")

[![hsaadi's 42 pipex Score](https://badge42.vercel.app/api/v2/cl5s2p211013909jutf782quk/project/2591096)](https://github.com/JaeSeoKim/badge42)