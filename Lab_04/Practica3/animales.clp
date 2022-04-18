
(deftemplate animal
(slot sangre)
(slot piel)
(slot mueve)
)

(deffacts animal-inicialmente
(animal (sangre nil) (piel nil) (mueve nil))
(hacer pregunta-sangre)
(hacer pregunta-piel)
(hacer pregunta-mueve)
)

(defrule pregunta-sangre
?anim <- (animal (sangre ?s) (piel ?p) (mueve ?m))
?pr <- (hacer pregunta-sangre)
=>
(printout t "¿El animal tiene sangre caliente o fria?(1, 2)" crlf)
(modify ?anim (sangre (read)))
(retract ?pr)
)

(defrule pregunta-mueve
?anim <- (animal (sangre ?s) (piel ?p) (mueve ?m))
?pr <- (hacer pregunta-mueve)
=>
(printout t "¿El animal anda o vuela?(1, 2)" crlf)
(modify ?anim (mueve (read)))
(retract ?pr)
)

(defrule pregunta-piel
?anim <- (animal (sangre ?s) (piel ?p) (mueve ?m))
?pr <- (hacer pregunta-piel)
=>
(printout t "¿El animal tiene piel con pelo, plumas, escamas o porosa? (1, 2, 3, 4)" crlf)
(modify ?anim (piel (read)))
(retract ?pr)
)

(defrule averiguar
(not (hacer pregunta-sangre))
(not (hacer pregunta-piel))
(not (hacer pregunta-pelo))
=>
(assert (es un sin_identificar))
)

(defrule mamifero
?es <- (es un sin_identificar)
(animal (sangre 1) (piel 1) (mueve 1))
=>
(retract ?es)
(assert (es un mamifero))
)

(defrule ave
?es <- (es un sin_identificar)
(animal (sangre 1) (piel 2) (mueve 2))
=>
(retract ?es)
(assert (es un ave))
)

(defrule reptil
?es <- (es un sin_identificar)
(animal (sangre 2) (piel 3) (mueve ?))
=>
(retract ?es)
(assert (es un reptil))
)

(defrule anfibio
?es <- (es un sin_identificar)
(animal (sangre 2) (piel 4) (mueve ?))
=>
(retract ?es)
(assert (es un mamifero))
)

(defrule murcielago
?es <- (es un sin_identificar)
(animal (sangre 1) (piel 1) (mueve 2))
=>
(retract ?es)
(assert (es un murcielago))
)

(defrule avestruz
?es <- (es un sin_identificar)
(animal (sangre 1) (piel 2) (mueve 1))
=>
(retract ?es)
(assert (es un avestruz))
)

(defrule imprime
(declare (salience -1))
(es un ?que)
=>
(printout t ?que crlf)
)
