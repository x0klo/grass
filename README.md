## grass

grass is functional grass-planting programming language.
This is C Language version.
Original version is [ちょっと草植えときますね型言語 Grass](http://www.blue.sky.or.jp/grass/).

## build and run

```shell
$ ./autogen.sh
$ ./configure
$ make
```

Introduction
Grass is a functional grass-planting programming language. Syntax and semantics of Grass are defined based on (A-normalized, lambda lifted, and De Bruijn indexed) untyped lambda calculus and SECD machine [Landin 1964] respectively so that Grass is Turing-complete.

Grass was first proposed by Katsuhiro Ueno at the 39th IPSJ Jouho-Kagaku Wakate no Kai (symposium for young researcher of information science) in 2006 to introduce how to define a programming language in formal way.

Grass is a kind of esoteric programming language typified by BrainF*ck, but Grass has unique characteristics which any other esoteric ones don't have. For example:

Grass is based on lambda calculus, not Turing machine.
Grass is slightly easier to read than functional programming languages designed based on combinatory logic.
Grass has formal definition.
Grass is easy to slip into ASCII art.
Sample programs
Print "w" to standard output.

wWWwwww
Calculate 1 + 1 and print the result by the number of "w". This example consists of 3 functions. First one is 1 represented by lambda term (Church integer). Second one is addition operator of Church integer. Last one is main function. This program is equivalent to (λi.(λmnfx.m f (n f x)) i i OUT w) (λfx.f x).

wwWWwv
wwwwWWWwwWwwWWWWWWwwwwWwwv
wWWwwwWwwwwWwwwwwwWwwwwwwwww

Intuitive explanation
A Grass program is written by using only "W", "w" and "v". Any other characters are ignored as comment. "W" and "v" appearing before first "w" are also ignored.

A Grass program consists of a list of top-level instructions separated by "v". The top-level instruction is either a function definition or a function application list. Every function definition starts with "w", and every function application list starts with "W".

Program :
    wwwwwWW ... wwWw v wwWWwW ... wWw v WWWwwwWw ... wwWWw v wW ...
    <---Function--->   <--Function-->   <--Applications-->
A function application list is a list of pairs of "W" sequence and "w" sequence. Every pair of "W" sequence and "w" sequence in a function application list denotes one function application, where the number of "W" is index of function and the number of "w" is index of argument.

Applications :
     WWWWWwwwwww WWWWWWwwwwwww ... WWWWwwww WW ...
    |<-5-><-6-->|<-6--><--7-->|   |  4  4  |
    |           |             |   |        |
    |  (5, 6)   |  (6, 7)     |   | (4, 4) |
    |   apply   |   apply     |   |  apply |
A function definition consists of a pair of arity and a function application list. The length of first "w" sequence of a function denotes arity of the function. What follows the arity is the function application list, that is, the function body. Note that only application may appear in function body; nested function is not allowed.

Function :
    wwwwww WWWWWwwwwww WWWWWWwwwwwww ... WWWWwwww  v
    <-6-->|<--- Applications (function body) --->|
          |           |             |   |        |
    6 args|  (5, 6)   |  (6, 7)     |   | (4, 4) |end of
          |   apply   |   apply     |   |  apply |function
Grass interpreter is a kind of stack-based machine (similar to SECD machine). Grass interpreter maintains a stack of values (called as environment in formal definition) during evaluation. Any values calculated by Grass program are pushed to this stack. Unlike any other popular stack-based machines, in Grass, once a value is pushed to the stack, the value is never popped; the stack of Grass interpreter grows only. Every value in the stack is indexed by sequentially ascending positive integer from the top of the stack to the bottom. In other words, index N indicates N-th value from top of the stack. Each index of the function application pair indicates this index.

Value Stack :

   1: value1    top of stack
   2: value2                          (1, 2) apply
   3: value3                           ^  ^
   ...                                 |  argument is 2nd value from top.
   N: valueN                           |
 -------------- bottom of stack      function is 1st value from top.
Evaluation of a Grass program is performed as follows:

Initialize the stack with system primitives, such as constant character and output function. See Primitives section for detail.
Evaluation starts from the beginning of the program and goes left-to-right.
If the interpreter meets a function definition, then the interpreter creates a function closure of the function with the whole of current stack, and pushes it to the stack.
If the interpreter meets a function application, then the interpreter takes a function closure and an argument indicated by the application from the stack, and call the function closure with the argument. The function body is evaluated immediately (Grass adopts eager evaluation) and the return value of the function is pushed to the stack. The evaluation of the function body is performed with stack saved in the function closure. The argument is pushed to the saved stack before the evaluation.
If the interpreter meets the end of function, then interpreter takes the top of the stack as return value, and resumes the evaluation of caller.
If the interpreter meets the end of program, then interpreter takes the top of the stack as a function, and call it with itself as argument. Return value of this function is the return value of the entire program.
Formal definition
Syntax
Only "W", "w", and "v" are used for a Grass program. Fullwidth version of these characters ("Ｗ" (U+FF37), "ｗ" (U+FF57), and "ｖ" (U+FF56)) are also accepted so that they are identical to non-fullwidth version characters. Any other characters may appear in a Grass program but they are ignored.

First character of a Grass program must be "w". Both "W" and "v" appearing before first "w" are ignored like any other characters than "W", "w", and "v".

The syntax of Grass is defined by the following BNF notation. X+ means repeat of X more than 1 time, and X* means repeat of X more than 0 time.

app ::= W+ w+
abs ::= w+ app*
prog ::= abs | prog v abs | prog v app*
app denotes function application, and abs denotes function abstraction. Valid Grass program, ranged over by prog, is a list of app and abs separated by "v".

Operational Semantics
To make the definition accurate, first we define abstract syntax of Grass as follows:

I ::= App(n, n) | Abs(n, C)
C ::= ε | I :: C
where n is an positive integer, and ε and :: are general list constructor denoting nil and cons, respectively. Intuitively, I ranges over the set of instructions and C ranges over the set of instruction list.

Correspondence between concrete syntax defined in previous section and the abstract syntax is trivially defined as follows:

app is corresponding to App(m, n), where m is the number of "W" and n is the number of "w".
abs is corresponding to Abs(n, C), where n is the number of "w" and C is an list of App corresponded to app*.
Thus prog is to be in C.
Additionally we define semantic object (ranged over f), environment (ranged over E), and suspended computation (ranged over D). D plays the same role as the dump of the SECD machine in Landin, so in what follows we call them dumps.

f ::= (C, E)
E ::= ε | f :: E
D ::= ε | (C, E) :: D
The operational semantics of Grass is defined through a set of rules to transform a machine configuration. A machine configuration is a triple (C, E, D) consisting of a code block C, an environment E, and a dump D. We write

(C, E, D) → (C', E', D')
if (C, E, D) is transformed to (C', E', D'). The reflexive transitive closure of → is denoted by →*.

Here is the set of transformation rules.

(App(m, n) :: C, E, D) → (Cm, (Cn, En) :: Em, (C, E) :: D) where E = (C1, E1) :: (C2, E2) :: … :: (Ci, Ei) :: E' (i = m, n)
(Abs(n, C') :: C, E, D) → (C, (C', E) :: E, D) if n = 1
(Abs(n, C') :: C, E, D) → (C, (Abs(n - 1, C')::ε, E) :: E, D) if n > 1
(ε, f :: E, (C', E') :: D) → (C', f :: E', D)
The top-level evaluation relation is defined as follows.

(C0, E0, D0) →* (ε, f :: ε, ε)
where E0 is initial environment defined in Primitives section, C0 is Grass program intended to be evaluated, and D0 is the initial dump such that

D0 = (App(1, 1)::ε, ε) :: (ε, ε) :: ε
If (C0, E0, D0) ↛* (ε, f :: ε, ε), then evaluation is stuck or never terminated.

Primitives
We define initial environment E0 for current version of Grass as follows. In future version, more primitives may be defined in the initial environment.

E0 = Out :: Succ :: w :: In :: ε
where Out, Succ, w, and In are primitives.

Primitives may have special behaviour and some side-effects. Although they cannot be described in pure lambda-calculus, we assume that every primitive is somehow encoded in the same manner as ordinary semantic object and behaves like ordinary function in the operational semantics. How to implement primitives are out of this document.

w
A value denoting an "w" character (code 119). Usually, a character is used as an argument for Out and Succ primitive, or is a return value of In primitive.

A character also performs as a function which returns equality between 2 characters; it takes an argument, and returns true of Church Boolean (λx.λy.x) if the argument is a character and is equivalent to the applied character, otherwise returns false of Church Boolean (λx.λy.y).

Out
Take a character as argument, print it to standard output, and return the given character. If the argument is not a character, evaluation will be aborted.

In
Take an arbitrary value as argument, read a character from standard input, and return it. If input reaches end of file, return the argument.

Succ
Take a character (code n) as argument and return its next character (code n+1) if n < 254. if n = 255, return a null character (code 0). If the argument is not a character, evaluation will be aborted.

From λ-Calculus to Grass
（あとで書く）

Start from untyped lambda calculus.

e ::= x | λx.e | e e
Perform CPS Transformation.

t ::= x | λx.r
c ::= k | μx.e
e ::= r c | x x c | c t
r ::= δk.e
Perform Inverse CPS Transformation.

e ::= x | λx.r | x x
r ::= e | let x = e in r
Perform Lambda Lifting so that all functions are to be at top-level.

e ::= x | x x
m ::= e | let x = e in m
f ::= λx.f | λx.m
r ::= e | let x = f in r | let x = e in r
Translate every variable name into de Bruijn Index.

n ::= • | n ↑
e ::= n | n n
m ::= e | let e in m
f ::= λf | λm
r ::= e | let f in r | let e in r
Plant grasses over this calculus. That's all.
