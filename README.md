# 42-minishell

**Score: 100/100**

This project is about making a command interpreter (shell) based on bash.

## Features

- Built-in commands: `cd` `pwd` `echo` `export` `unset` `env` `exit`
- Signal handling: `CTRL-C` `CTRL-\` `CTRL-D` (not quite signal but...)
- Pipes `|`
- Redirections `>` `<` `>>` `<<`
- Local variables
- Environment expansions and exit status `$?`
- Quotes `'` `"`

## How It Works

The program has 4 main sections: **`Splitter`** -> **`Lexer`** -> **`Parser`** -> **`Executor`**

Let's say our example input is `ls -la | wc -l`

In **`Splitter`** we are dividing input into meaningful parts and store those in a string array (2D char array).
`ls`
`-la`
`|`
`wc`
`-l`

In **`Lexer`** we are looking at the meaningful parts and determine their type.
`ls = COMMAND`
`-la = ARGUMENT`
`| = PIPE`
`wc = COMMAND`
`-l = ARGUMENT`

In **`Parser`** we are creating command blocks.
```
{
  cmd = ls
  args = [-la]
  in = stdin
  out = pipe
}
{
  cmd = wc
  args = [-l]
  in = pipe
  out = stdout
}
```

In **`Executor`** we are simply executing the command blocks.

## Usage

If you are on Linux just use `make` and it will give the executable `minishell` program.

If you are on Mac you have to edit the Makefile. Comment the line under the "FOR LINUX" and uncomment the line under the "FOR MAC" part. Then use `make` to get the executable `minishell` program.

After compiling it use it like `./minishell`.

![Visual](./assets/minishell.png)
