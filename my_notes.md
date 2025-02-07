# Copy from server

~~~
rsync -avz mhpc25-06@ssh.hca.bsc.es:/home/mhpc25-06/monday_03 /home/gustavo/Documents/MHPC2425/P2.3_arch_24_25/
~~~

# to get the processor info 
For example when we do:
~~~
lscpu
~~~
in the part that sees:
~~~
Model name:                      Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
~~~
so we put **E5-2620V4** in this page:
~~~
https://www.intel.com/content/www/us/en/ark.html
~~~

# Hand on second day
 
my solution codes:

R1 - https://repo.hca.bsc.es/epic/z/GPZHJ6

R2 - https://repo.hca.bsc.es/epic/z/wKpSPJ

R3 - https://repo.hca.bsc.es/epic/z/IeLLli

R4 - https://repo.hca.bsc.es/epic/z/ourb9l

# Repo tho dowload the compiler

https://repo.hca.bsc.es/epic/z/rRFc_I 

And teh files to have "#include "rave_user_events.h" and 
~~~
https://repo.hca.bsc.es/gitlab/pvizcaino/rave/-/tree/refactor
~~~

# sshfs 

To use a interfase in a server 

# Theory for exam
This is like a summary of theory 

* Instruction Set Architecture
	* Definition of ISA

			Instruction Set Architecture:
			This is the set of instructions and regulations that define how a processor (CPU) interacts with the software and hardware.
			define what a processor can do and how it should be executed, without specifying how it is physically implemented in the hardware.

			Examples:

			x86 (Intel and AMD) → Common on desktop computers and servers.

			ARM → Used on mobile devices, embedded and low power servers.

			RISC-V → ISA open and modular in growth. 

	* Difference between ISA/Architecture and Implementation/Micro-architecture

			Refers to how an ISA is implemented in hardware, including the internal organization of the processor.

	* Instruction encodings
		* Types of operations, operands, and addressing modes

			El opcode (operational code) es la parte de la instrucción que indica qué operación se debe ejecutar.

				Ejemplos de tipos de operaciones en una ISA:
				Aritméticas → ADD, SUB, MUL, DIV
				Lógicas → AND, OR, XOR, NOT
				Carga y almacenamiento → LOAD, STORE
				Transferencia de control → JUMP, CALL, RETURN
				Operaciones especiales → NOP, HLT

			Los operandos son los valores sobre los cuales opera la instrucción. Pueden ser:

				Registros → La CPU opera sobre registros internos (R1, R2, R3 en ARM, $t0, $t1, $t2 en MIPS).
				Constantes inmediatas → Un número directo en la instrucción (5, 10, etc.).
				Direcciones de memoria → La instrucción puede operar sobre una dirección en RAM.

			Los modos de direccionamiento especifican cómo se obtiene el operando. Es la forma en que la CPU accede a los datos.

				Inmediato (Immediate Addressing)
				El operando es un valor directo dentro de la instrucción.
				MOV AX, 10  ; AX = 10 (10 está en la instrucción)

				Registro (Register Addressing)
				La instrucción usa un valor almacenado en un registro de la CPU.
				ADD AX, BX  ; AX = AX + BX (usa valores en registros)

				Directo (Direct Addressing)
				La instrucción usa una dirección de memoria específica.
				MOV AX, [1000]  ; AX = valor en dirección 1000

				Indirecto (Indirect Addressing)
				La dirección del operando está en un registro o en memoria.
				MOV AX, [BX]  ; AX = valor en la dirección contenida en BX

				Indexado (Indexed Addressing)
				Usa un registro base más un desplazamiento (offset).
				MOV AX, [BX+SI]  ; AX = valor en dirección (BX + SI)

				Relativo (Relative Addressing)
				Usado para saltos (JMP, CALL), especifica una dirección relativa al valor actual del contador de programa.
				JMP +10  ; Salta 10 instrucciones adelante

		* Fixed vs Variable length

			Fixed/Variable 

				Cada instrucción tiene un tamaño fijo/variable en bits, lo que facilita su decodificación en hardware y permite un pipeline más eficiente. Este enfoque es común en arquitecturas RISC (Reduced Instruction Set Computing).

				Se debe considerar: EL uso del espacio, el tiempo de decoficicacion, el uso y optimizacion de pipelines 



* Pipelining

   hello 

	* Definition of **hardware pipelining** and Instruction Level Parallelism

      	En el contexto de procesadores, pipelining divide la ejecución de una instrucción en varias etapas, y cada etapa se ejecuta en paralelo con otras instrucciones.


	* Identification of stages in a pipeline (IF, ID, RD, etc.)

				(RISC)
				Fetch (IF - Instruction Fetch) → Se busca la instrucción en memoria.
				Decode (ID - Instruction Decode) → Se decodifica la instrucción y se identifican operandos.
				Execute (EX - Execute) → Se realiza la operación en la ALU (suma, resta, multiplicación, etc.).
				Memory (MEM - Memory Access) → Se accede a memoria si la instrucción lo requiere (ej. LOAD, STORE).
				Write-back (WB - Write Back) → Se guarda el resultado en el registro correspondiente.

				|1 |2 |3 |4  |5  |6  |7 |
				|--|--|--|---|---|---|---|
				|IF|ID|EX|MEM|WB |	 |   |
				|  |IF|ID|EX |MEM|WB |	 |
				|  |  |IF|ID |EX |MEM|WB |


				Un problema puede ser:
				LW R1, 0(R2)    # R1 = valor en memoria (R2)
				ADD R3, R1, R4  # R3 = R1 + R4 (R1 aún no tiene el valor cargado)

				Técnicas como forwarding (reenvío) o stalls (paradas de pipeline) pueden usarse para evitar errores.

		El **Paralelismo a Nivel de Instruccion** (ILP) es la capacidad de ejecutar múltiples instrucciones simultáneamente en un procesador para mejorar el rendimiento.

				Tipos de ILP:

				Pipelining: Superposición de etapas de ejecución de múltiples instrucciones.
				Superscalar: Se ejecutan múltiples instrucciones en el mismo ciclo de reloj.
				Out-of-Order Execution (OoO): Las instrucciones no tienen que ejecutarse en el orden del programa si hay independencia de datos.
				VLIW (Very Long Instruction Word): Se agrupan varias operaciones en una sola instrucción de longitud fija.


	* Identification of hardware resources (Instruction Memory, Decoding Logic, Register File, etc.)

		Es la memoria que almacena las **instrucciones** del programa que la CPU va a ejecutar. Puede ser:

				Memoria Caché de Instrucciones (L1 I-Cache): Almacena instrucciones usadas frecuentemente.
				Memoria RAM: Almacena el código del programa antes de ser cargado en caché.	

		**Decoding** Es el hardware que interpreta y convierte la instrucción en señales de control para las unidades funcionales del procesador.

				¿Cómo funciona?

				La instrucción se recibe desde la memoria de instrucciones.
				La unidad de decodificación separa los campos de la instrucción:
				Opcode → Define la operación (ADD, MOV, LW).
				Operandos → Registros o direcciones de memoria involucradas.
				Modo de direccionamiento → Cómo se accede a los datos.

		**Register File** (Banco de Registros)

				¿Qué es?
				Es un conjunto de registros internos en la CPU que almacenan datos temporales.

				Ejemplo de registros comunes:

				Registros de propósito general → Almacenan valores intermedios (ej. EAX, EBX en x86, $t0, $t1 en MIPS).
				Registros de segmento/puntero → Apuntan a direcciones de memoria (ESP, EBP en x86).
				Registros de control → Contienen información sobre el estado del procesador (EFLAGS, PC en x86).

	* Hazards

		Los hazards son problemas que ocurren en un procesador pipelined cuando una instrucción no puede ejecutarse correctamente debido a conflictos con otras instrucciones en el pipeline.

		* Definition of Data Hazard

				Ocurre cuando una instrucción depende del resultado de una instrucción anterior que aún no ha terminado de ejecutarse.
				LW   $t1, 0($t2)  # Carga un valor desde memoria a $t1
				ADD  $t3, $t1, $t4  # Intenta usar $t1 antes de que tenga el valor correcto

				Sol Data Hazards:

				Forwarding (Reenvío de datos): Se pasa el resultado de una etapa posterior a una anterior sin esperar el ciclo completo.
				Pipeline Stalling (Detención del pipeline): La CPU inserta ciclos de espera (NOPs) para retrasar la ejecución hasta que los datos estén disponibles.

		* Definition of Control Hazard

				Ocurre cuando la CPU no sabe qué instrucción ejecutar a continuación debido a una instrucción de salto o bifurcación (JMP, BEQ, CALL).
				BEQ $t1, $t2, LABEL  # Si $t1 == $t2, salta a LABEL
				ADD $t3, $t4, $t5  # ¿Se ejecuta o no?

				Sol Control Hazards:

				Branch Prediction (Predicción de bifurcación): Se intenta adivinar el resultado del salto antes de que se complete la evaluación.
				Branch Delay Slot: Algunas arquitecturas (como MIPS) ejecutan la instrucción inmediatamente después del salto sin importar si se toma la bifurcación o no.
				Pipeline Flushing (Descarga del pipeline): Se eliminan las instrucciones incorrectas y se vuelve a cargar la correcta, pero esto reduce el rendimiento.

		* Definition of Structural Hazard

				Ocurre cuando dos instrucciones compiten por el mismo recurso de hardware al mismo tiempo.
				El hardware no tiene suficientes recursos para ejecutar múltiples instrucciones simultáneamente.

				Ejemplo
				Supón que un procesador tiene una sola ALU y dos instrucciones necesitan usarla simultáneamente:

	* Workarounds
		* Bypassing/Forwarding : To solve Data Hazards
		* Branch prediction : to solve Control Hazards
		* Adding hardware resources: to solve structural Hazards

* Memory hierarchy
	* Motivation on caches

				La CPU es mucho más rápida que la RAM.
				Acceder a memoria RAM es costoso en tiempo, por lo que es más eficiente usar cachés más rápidas y cercanas al procesador.

	* Mapping policies

				Como la caché tiene menos capacidad que la RAM, se debe decidir dónde almacenar los datos en la caché.

		* Definition of Direct mapping

				Cada bloque de memoria principal solo puede ir a una única posición en la caché.
				Se usa una función simple para asignar bloques:
				index_cache =direction_memory modulo  Numero_bloques_cache

		* Definition of Fully-Associative mapping

				Un bloque de memoria puede ir a cualquier parte de la caché.
				No hay restricciones de ubicación como en el mapeo directo.

		* Definition of Set-Associative mapping

				Es un punto intermedio entre direct-mapped y fully-associative.
				La caché se divide en conjuntos (sets) y cada bloque de memoria se asigna a un conjunto específico, pero dentro del conjunto puede colocarse en cualquier bloque disponible.

	* Definition of replacement policies (and naming some example)

				Cuando la caché está llena, se debe decidir qué bloque eliminar para hacer espacio a nuevos datos.

				Ejemplos de Políticas de Reemplazo:

				FIFO (First In, First Out) → Se reemplaza el bloque más antiguo.
				LRU (Least Recently Used) → Se elimina el bloque menos usado recientemente.
				Random → Se selecciona un bloque al azar para eliminar.
				LFU (Least Frequently Used) → Se elimina el bloque con menos accesos.

	* Definition of write policies (write-back vs write-through)

				Cuando la CPU modifica datos, ¿cómo aseguramos que estos cambios lleguen a la RAM? Existen dos estrategias:

				Write-Through (Escritura Directa)
				Cada vez que la CPU escribe en la caché, también escribe en la RAM inmediatamente.
				Se mantiene la memoria siempre actualizada, pero es más lento.

				Write-Back (Escritura Diferida)
				La CPU escribe solo en la caché y marca el bloque como "modificado".
				Solo cuando el bloque se reemplaza en caché, se escribe en la RAM.

	* Motivation for Virtual Memory (swap?)

				 La RAM es limitada, pero la memoria virtual permite expandirla usando espacio en disco.
				Permite ejecutar programas más grandes que la memoria RAM disponible.
				Aísla procesos para seguridad y estabilidad.

				¿Cómo funciona?

				Cada proceso ve una dirección de memoria virtual, no la dirección física real.
				Cuando un dato no está en RAM, se usa el swap en disco (página virtual → página en RAM).
				Se usa una MMU (Memory Management Unit) para traducir direcciones virtuales a físicas.

* Data Level Parallelism

				El paralelismo a nivel de datos (DLP) se refiere a la ejecución simultánea de la misma operación en múltiples elementos de datos. Se usa en procesadores SIMD y procesadores vectoriales para mejorar el rendimiento en aplicaciones científicas, gráficas y de inteligencia artificial.

	* Definition of SIMD (Single Instruction, Multiple Data - Array Processor) (Array Processor)

				En SIMD, una sola instrucción se ejecuta en múltiples datos al mismo tiempo.
				Se usa en procesadores gráficos (GPUs), extensiones como AVX, SSE (Intel), NEON (ARM) y computación científica.

				// Versión escalar (sin SIMD)
				for (int i = 0; i < 4; i++) 
    				C[i] = A[i] + B[i];
				// Versión SIMD (4 elementos a la vez)
				C = A + B;  // Se usa una instrucción SIMD para procesar 4 datos en paralelo


	* Definition of Vector Processor

				Es un procesador especializado que opera en vectores completos, en lugar de hacerlo en un solo valor a la vez.
				Se encuentra en supercomputadoras y arquitecturas como Cray-1.

	* Types of vector instructions (arithmetic, memory, reductions, etc.)
		* Arithmetic (add, mul, etc.)

				Operaciones en vectores como suma, multiplicacion dot product etc. 

		* Memory (unit-strided, strided, indexed)


				Los accesos a memoria pueden optimizarse dependiendo de cómo se almacenan los datos en la caché:

				Unit-Strided → Los datos son contiguos en memoria.
				LOAD V1, [R1]  // Carga V1 desde memoria en R1 (contiguo)
				Strided → Los datos tienen un paso (stride) fijo.
				LOAD V1, [R1 + STRIDE]  // Carga cada elemento con un desplazamiento
				Indexed → Los datos se encuentran en posiciones dispersas.
				LOAD V1, [INDEX_ARRAY]  // Carga usando un índice arbitrario

		* Reductions

				Realizan operaciones de reducción como sumas o productos en un vector completo.
				Ejemplo:
				VREDUCE_SUM V1  // Suma todos los elementos de V1 en un solo valor

		* Conditionals (masked operations)

				Ejecutan operaciones condicionales en vectores.
				Ejemplo:
				VMASKED_ADD V1, V2, MASK  // Suma solo si la máscara lo permite reduce bifurcaciones if-else

	* Memory locality on vector processors
		* Which type of memory accesses are cache-friendly

				La eficiencia de la caché depende de cómo se organizan los datos en memoria.

				Unit-strided (datos contiguos) → Rápidos, aprovechan la prefetching de la caché.
				Strided o Indexed → Más lentos, pueden causar cache misses.

		* Example of Array of Structs vs Struct of Arrays

				Array of Structs AoS 
				El rendimiento depende de cómo se almacenen los datos en memoria.
				// Arreglo de estructuras
				struct Particle {
    				float x, y, z;
				};
				Particle particles[N];  
				//Si solo necesitamos x, los accesos a y y z desperdician caché.

				Struct of Arrays
				// Estructura con arreglos separados
				struct ParticleArray {
    				float x[N], y[N], z[N];
				};
				ParticleArray particles; 
				// Ventaja Puede vectorizar operaciones sobre x sin cargar datos innecesarios.

* RISC-V

				RISC-V es una arquitectura de conjunto de instrucciones (ISA) RISC que es abierta y modular.
				A diferencia de otras ISAs (x86, ARM), no está patentada, permitiendo a cualquiera implementarla sin pagar licencias.

	* Incremental vs Modular ISAs

				Incremental ISA	La ISA crece en funcionalidad añadiendo nuevas instrucciones sobre un núcleo fijo.	x86-64 evoluciona con nuevas extensiones como AVX, AVX-512.

				Modular ISA	Enfoque basado en módulos opcionales en lugar de crecimiento lineal.	RISC-V permite elegir solo las extensiones necesarias (I, M, F, D, V).

	* Definition of Extension, Profile, Mode (aka Privilege level), and Platform in the context of RISC-V

				Extension	Un conjunto de instrucciones adicionales opcionales.	M (multiplicación), V (vectores).
				Profile	Conjunto recomendado de extensiones para una aplicación específica.	Embedded, Server, AI.
				Mode (Privilege Level)	Define niveles de acceso del CPU.	User (U), Supervisor (S), Machine (M).
				Platform	Especificaciones de hardware/software compatibles con RISC-V.	SoC con RV64GC, soporte de Linux.

				Ejemplo de Privilege Levels en RISC-V

				Modo Machine (M) → Máxima autoridad, controla la CPU y memoria.
				Modo Supervisor (S) → Para sistemas operativos, gestiona memoria virtual.
				Modo User (U) → Nivel más bajo, ejecuta aplicaciones sin acceso privilegiado.

* RISC-V vector extension (rvv)

				Es la extensión vectorial de RISC-V (V) que permite ejecutar operaciones vectoriales en hardware especializado.

	* Definition of VLEN, sew, and vl

				VLEN: Tamaño máximo de un vector en bits. Ejemplo: VLEN=512 bits.
				sew (Standard Element Width):	Tamaño de cada elemento del vector (8, 16, 32, 64 bits).
				vl (Vector Length):	Número de elementos vectoriales activos en una operación.

				Si VLEN = 512 bits y SEW = 32 bits:
            	vl = VLEN / sew = 512 / 32 = 16 elementos
				El procesador puede procesar 16 elementos en paralelo.

	* Ways of vectorizing and their trade-offs


		* Auto-vectorization (hope that the compiler does everything)

				Auto-vectorización (Esperar que el compilador lo haga todo)
				Fácil de usar.
				Depende de la eficiencia del compilador (puede no vectorizar correctamente).
				#pragma omp simd
				for (int i = 0; i < N; i++) 
    				C[i] = A[i] + B[i];

		* Using pragmas

				Mejor control.
				Depende del compilador y de la plataforma.
				#pragma vector always
				for (int i = 0; i < N; i++) 
    				C[i] = A[i] + B[i];


		* Manual vectorization via intrinsics

				Máximo control.
				Código menos portátil y más complejo.
				vfloat32m1_t v1 = vle32_v_f32m1(&A[i]);
				vfloat32m1_t v2 = vle32_v_f32m1(&B[i]);
				vfloat32m1_t v3 = vfadd_vv_f32m1(v1, v2);
				vse32_v_f32m1(&C[i], v3);

	* Definition of vectorization metrics
		* Average VectorLength (AvgVL)

				Average Vector Length (AvgVL) → Promedio de elementos procesados por vector.
				AvgVL = (Σ Vector Length en cada instrucción) / (Total instrucciones vectoriales)
				Cuanto más alto, mejor aprovechamiento del hardware.

		* Vector Mix

				Vector Mix → Porcentaje de operaciones vectoriales vs. escalares.
				Vector Mix = (# Instrucciones vectoriales / Total de instrucciones) * 100%
				Un Vector Mix alto indica un programa bien vectorizado.

* EPAC architecture (European Processor Accelerator)

				EPAC es un acelerador del EPI Project (European Processor Initiative) que incluye una Unidad de 
				Procesamiento Vectorial (VPU) optimizada para HPC.

	* Context of EPI project, EPAC (EPI Accelerator), and the Vector Processing Unit (VPU) inside it
	* Characterization of the VPU in EPAC
		* What is the VLEN (bits) or maximum VL (elements)?

				VLEN (bits)	512
				Máximo vl (elementos)	Depende de sew (ej. 512/32 = 16 elementos).

		* What is the number of lanes (functional units) and how it relates to the performance of vector instructions?

				Lanes (Unidades Funcionales)	8
				Tipo de operaciones	Aritmética, Memoria, Reducción, Máscara.

				Relación entre Lanes y Performance
				Cada lane ejecuta una parte del vector en paralelo.
				Si hay 8 lanes, el procesador puede dividir VL entre 8 para procesar más rápido.

		EPAC y RISC-V Vector Extension (RVV) trabajan juntos para computación de alto rendimiento en Europa.

		
