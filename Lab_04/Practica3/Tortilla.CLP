;FACTS
(deffacts condiciones-iniciales
(hay naranjas)
(hay patatas)
(hay huevos)
(hay pimientos)
)

;RULES
(defrule posible-tortilla-sin-cebolla
   (hay patatas)
   (hay huevos)
=>
   (printout t "Se puede hacer una tortilla de patatas sin cebolla." crlf)
)

(defrule posible-tortilla-con-cebolla
   (hay patatas)
   (hay huevos)
   (hay cebolla)
=>
   (printout t "Se puede hacer una tortilla de patatas con cebolla." crlf)
)
