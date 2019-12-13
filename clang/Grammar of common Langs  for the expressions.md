# Grammar of common Langs for the expressions

```go
<Expression>		:= <Literal> | <NamedValue> | <MatcherExpression>
<Literal>			:= <StringLiteral> | <Boolean> | <Double> | <Unsigned>
<StringLiteral>		:= "quoted string"
<Boolean>			:= true | false
<Double>			:= [0-9]+.[0-9]* | [0-9]+.[0-9]*[eE]*[-+]?[0-9]+
<Unsigned>			:= [0-9]+
<NamedValue>		:= <Identifier>
<MatcherExpression>	:= <Identifier>(<ArgumentList>) |
						<Identifier>(<ArgumentList>).bind(<StringLiteral>)
<Identifier>		:= [a-zA-Z]+
<ArgumentList>		:= <Expression> | <Expression>,<ArgumentList>
```