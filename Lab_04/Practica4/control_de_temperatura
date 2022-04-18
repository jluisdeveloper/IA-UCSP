(deftemplate MAIN::valvula
    (slot nombre
        (type SYMBOL)
    )
    (slot temperatura
        (type NUMBER)
    )
)

(defmodule MAIN (export deftemplate valvula))
(defmodule LEER (import MAIN deftemplate valvula))
(defmodule ESCRIBIR (import MAIN deftemplate valvula))

(defrule LEER::input
    =>
    (open "C:/Users/anarchist/Desktop/temperaturas.dat" auxiliarfich "r")
    (bind ?valor (read auxiliarfich))
    (while (neq ?valor EOF) do
        (assert(valvula (nombre ?valor)(temperatura (read auxiliarfich))))
        (bind ?valor (read auxiliarfich))
    )
    (close auxiliarfich)
)

(defrule ESCRIBIR::abrir
    (declare (salience 3))
    =>
    (open "C:/Users/anarchist/Desktop/alarmas.out" alarmas "w") ;w de write
)

(defrule ESCRIBIR::comprobacionTemperaturaMenor
    (declare (salience 2))
    (valvula (nombre ?nombre)(temperatura ?temp))
    (test(< ?temp 95))
    =>
    (printout alarmas ?nombre " " ?temp crlf)
)

(defrule ESCRIBIR::comprobacionTemperaturaMayor
    (declare (salience 2))
    (valvula (nombre ?nombre)(temperatura ?temp))
    (test(> ?temp 95))
    =>
    (printout alarmas ?nombre " " ?temp " AlarmaActivada" crlf)
)

(defrule ESCRIBIR::cerrar
    (declare (salience 1))
    =>
    (close alarmas)
)

(defrule MAIN::run
    =>
    (focus ESCRIBIR)
    (focus LEER)
)
