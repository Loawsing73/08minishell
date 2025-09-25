pipeline     -> command '|' pipeline
pipeline     -> command

command      -> word argument_list redirection_list
argument_list -> argument argument_list
argument_list -> ε (vide)

argument     -> word
argument     -> quoted_string

redirection_list -> redirection redirection_list  
redirection_list -> ε

redirection  -> '<' word
redirection  -> '>' word
redirection  -> '<<' word
redirection  -> '>>' word

quoted_string -> QUOTE content QUOTE
quoted_string -> DOUBLE_QUOTE content DOUBLE_QUOTE

word         -> WORD



test Nico:
-expand $ -> rien
-si $US (ou US existe pas) -> rien 
->>> -> >> puis pas > comme token redirect