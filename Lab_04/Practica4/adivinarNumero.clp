

(deffacts myfacts
 (bucle)
 )

(defglobal ?*secretNum* = (random 1 100))


(defrule adivinar
    ?bucle <- (bucle)
    =>
    (printout t "adivina numero: "  crlf)
    (bind ?resp (read))
    (if (eq ?resp ?*secretNum*)
        then
            (printout t "correcto!! el numero es: " ?resp  crlf)
            (retract ?bucle) 
            (halt)
        else
            (retract ?bucle)
            (assert (bucle)) 
    ) 
)



