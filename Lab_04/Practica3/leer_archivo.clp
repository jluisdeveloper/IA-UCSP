(deftemplate persona 
    (slot nombre)
    (slot apellido1)
    (slot apellido2)
)

(deffacts inicio
    (leer)
)

(defrule lectura-files
    
    (leer)
  => 
   (open "C:\\Users\\Misash\\Documents\\UCSP\\IA\\IA-UCSP\\Lab_04\\Practica3\\facts.txt" data "r")
    (bind ?data (explode$ (readline data)))
    (while (neq ?data EOF)
      (assert 
        (persona
            (nombre (nth$ 1 ?data))
            (apellido1 (nth$ 2 ?data))
            (apellido2 (nth$ 3 ?data))
        )
        )
       (printout t ?data  crlf)
       (bind ?data (explode$ (readline data )))
    )
    (close data)
)
