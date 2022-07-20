" Vim syntax file
" Language: Hack

" Usage Instructions
" Put this file in .vim/syntax/hack.vim
" and add in your .vimrc file the next line:
" autocmd BufRead,BufNewFile *.hack set filetype=hack

if exists("b:current_syntax")
  finish
endif

syntax keyword hackTodos TODO XXX FIXME NOTE

" Language keywords
syntax keyword hackKeywords nop push drop dup
syntax keyword hackKeywords plusi minusi multi divi modi
syntax keyword hackKeywords plusf minusf multf divf
syntax keyword hackKeywords jmp jmp_if halt swap not
syntax keyword hackKeywords eqi gei gti lei lti nei
syntax keyword hackKeywords eqf gef gtf lef ltf nef
syntax keyword hackKeywords ret call native
syntax keyword hackKeywords andb orb xor shr shl notb
syntax keyword hackKeywords read8 read16 read32 read64
syntax keyword hackKeywords write8 write16 write32 write64
syntax keyword hackKeywords i2f u2f f2i f2u

" Comments
syntax region hackCommentLine start=";" end="$"   contains=hackTodos
syntax region hackInclude start="%include" end=" "

" Numbers
syntax match hackDecInt display "\<[0-9][0-9_]*"
syntax match hackHexInt display "\<0[xX][0-9a-fA-F][0-9_a-fA-F]*"
syntax match hackFloat  display "\<[0-9][0-9_]*\%(\.[0-9][0-9_]*\)"

" Strings
syntax region hackString start=/\v"/ skip=/\v\\./ end=/\v"/
syntax region hackCharacter start=/\v'/ skip=/\v\\./ end=/\v'/

" Set highlights
highlight default link hackTodos Todo
highlight default link hackKeywords Keyword
highlight default link hackCommentLine Comment
highlight default link hackInclude PreProc
highlight default link hackDecInt Number
highlight default link hackHexInt Number
highlight default link hackFloat Float
highlight default link hackString String
highlight default link hackCharacter String

let b:current_syntax = "hack"
