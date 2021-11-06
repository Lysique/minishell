
# PROJECT FILE STRUCTURE
```
minishell  
├── includes  
│   └── minishell.h  
├── libs  
│   ├── garbage_collector  
│   └── libftprintf  
│       ├── includes  
│       ├── libft-------------->// LIBFT library  
│       ├── Makefile  
│       ├── srcs  
│       └── srcs_bonus  
├── README.md  
└── srcs  
    ├── executor ------------->//STEP 4: execute commandlist  
    │   └── README.md  
    ├── expander-------------->//STEP 3: expand variables and wildcards  
    │   └── README.md  
    ├── lexer------------------>//STEP 1: split input string into tokens  
    │   └── README.md  
    ├── minishell.c  
    └── parser----------------->//STEP 2: parse tokens into valid command list  
        └── README.md  
 ```
# Resources  
[Shell architecture "Lexer->Parser->Expander->Executor"](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
