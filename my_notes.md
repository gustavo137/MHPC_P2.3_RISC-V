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
	* Instruction encodings
		* Types of operations, operands, and addressing modes
		* Fixed vs Variable length

* Pipelining

   hello 

	* Definition of hardware pipelining and Instruction Level Parallelism

      hello2

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
