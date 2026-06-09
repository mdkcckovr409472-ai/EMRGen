The main steps for generating EMRs with EMRGen are as follows:

1. Use an LLM to automatically extract program information and generate test generation functions, which construct follow-up inputs from source inputs.
2. Mine cross‑execution relationships using the dynamic invariant detector (Daikon) and convert the invariants into MR checking functions with the help of an LLM.
3. Compile, execute, and validate the generated EMRs, filtering out those that are not executable or incorrect, and retain the valid EMRs that can be directly used for metamorphic testing.

You can run `batch.py` to generate EMRs from the target program as follows:

`python batch.py bubble/bubble.cpp`

After running, the corresponding execution results will be given.