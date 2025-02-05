# P2.3_arch_24_25

* Fabio Banchelli: fabio.banchelli [at] bsc.es
* Pablo Vizcaino: pablo.vizcaino [at] bsc.es
* Filippo Mantovani: filippo.mantovani [at] bsc.es


----


Booking a slot for the evaluation
	* Use the following link to book a 30min slot: https://cal.com/filimanto/30min

Grading method
	* 10min presentation (slides or any graphical support of your own choosing) including the following topics
		* Lab1 Micro-benchmarks
		* Lab2 Vectorization challenges
		* Lab3 Vectorization of ConjugateGradient
		* Complete the table in Slide #14"Sizing an HPC system" of "MHPC25_-_07-EPI_EPAC_intro" and discuss about it
	* 15min of questions (from us to you) relating to your presentation
		* Have a look at the list below for a categorization of topics
	* Optional 2min pitch
		* Take one topic from the list "Advanced Architecture"

Theory contents that can be asked during the evaluation
	* Instruction Set Architecture
		* Definition of ISA
		* Difference between ISA/Architecture and Implementation/Micro-architecture
		* Instruction encodings
			* Types of operations, operands, and addressing modes
			* Fixed vs Variable length
	* Pipelining
		* Definition of hardware pipelining and Instruction Level Parallelism
		* Identification of stages in a pipeline (IF, ID, RD, etc.)
		* Identification of hardware resources (Instruction Memory, Decoding Logic, Register File, etc.)
		* Hazards
			* Definition of Data Hazard
			* Definition of Control Hazard
			* Definition of Structural Hazard
		* Workarounds
			* Bypassing/Forwarding
			* Branch prediction
			* Adding hardware resources
	* Memory hierarchy
		* Motivation on caches
		* Mapping policies
			* Definition of Direct mapping
			* Definition of Fully-Associative mapping
			* Definition of Set-Associative mapping
		* Definition of replacement policies (and naming some example)
		* Definition of write policies (write-back vs write-through)
		* Motivation for Virtual Memory
	* Data Level Parallelism
		* Definition of SIMD (Array Processor)
		* Definition of Vector Processor
		* Types of vector instructions (arithmetic, memory, reductions, etc.)
			* Arithmetic (add, mul, etc.)
			* Memory (unit-strided, strided, indexed)
			* Reductions
			* Conditionals (masked operations)
		* Memory locality on vector processors
			* Which type of memory accesses are cache-friendly
			* Example of Array of Structs vs Struct of Arrays
	* RISC-V
		* Incremental vs Modular ISAs
		* Definition of Extension, Profile, Mode (aka Privilege level), and Platform in the context of RISC-V
	* RISC-V vector extension (rvv)
		* Definition of VLEN, sew, and vl
		* Ways of vectorizing and their trade-offs
			* Auto-vectorization (hope that the compiler does everything)
			* Using pragmas
			* Manual vectorization via intrinsics
		* Definition of vectorization metrics
			* Average VectorLength (AvgVL)
			* Vector Mix
	* EPAC architecture
		* Context of EPI project, EPAC (EPI Accelerator), and the Vector Processing Unit (VPU) inside it
		* Characterization of the VPU in EPAC
			* What is the VLEN (bits) or maximum VL (elements)?
			* What is the number of lanes (functional units) and how it relates to the performance of vector instructions?

Advanced Architecture topics. Pick one and do a 2min pitch of it for extra points :)
	* Single-core
		* Definition and implications of multi-cycle pipeline
		* Definition and implications of dynamic scheduling (Out-of-Order execution)
		* Definition and implications of superscalar pipelines
	* Multi-core
		* Explanation of limits of single-core systems
		* Definition of Concurrency and distinction between Multiplexing and Parallelizing
	* Shared Memory
		* Definition and description of a Symmetric Multi-Processor (SMP)
		* Definition of Coherence and Consistency
	* Distributed Memory
		* Limitations of Uniform Memory Access (UMA) and motivation of Non-Uniform Memory Access (NUMA)
		* Distinction between Shared Memory and Distributed Memory
		* Definition and motivation of Direct Memory Access (DMA) engines

