(defrule open-files
=>
   (open "datos.dat" entrada "r")
   (assert (phase read-from-file))
)

(defrule read-data
   ?phase-adr <- (phase read-from-file)
=>
   (retract ?phase-adr)
   (bind ?nombre (read entrada))
   (bind ?apellido1 (read entrada))
   (bind ?apellido2 (read entrada))

   (if (eq ?nombre EOF)
   then (close entrada)
       (halt)
   )

   (if (neq ?nombre EOF)
   then (assert (persona ?nombre ?apellido1 ?apellido2))
   )
   (assert (phase read-from-file))
)