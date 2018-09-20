# 7542 - Taller de Programación

### 2do Cuatrimestre 2018

## TP1: Minimal Remote Java Virtual Machine

* #### compilar desde src/: make tp

* #### correr desde src/: 
    - Modo cliente: ./tp client &lt;host&gt; &lt;port&gt;​ &lt;N&gt; [&lt;filename&gt;​]
    - Modo servidor: ./tp server &lt;port&gt;
  
El objetivo de este ejercicio es acceder, mediante la instancia de cliente, a un servidor el cual contiene un maquina virtual que ejecuta un subconjunto de instrucciones de una JVM. El cliente leerá una serie de instrucciones conocidas como byte codes y se las enviará al servidor para que el servidor las ejecute junto con el tamaño del array de variables N.
