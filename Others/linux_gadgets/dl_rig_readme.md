# deep learning rig configuration

## 1. virtual environment

using kubuntu-desktop instead of gnome (memory starved)

using python3.7 instead of 3.5, with cuda-10.0 and cudnn-7.6 acceleration

**notice : please do not use native python3 or python, you may encounter runtime error and version mismatch.**

#### pytorch/fastai/jupyter

notice : pytorch encountered compatibility issues with latest RTX card, torch GPU check passed, while when ran models with jypyter notebook, CUDA runtime crashed.

> source ~/vfastai/bin/activate

#### tensorflow

> source ~/vtf/bin/activate

#### paddle paddle gpu

> source ~/vpp/bin/activate

#### opencv

> source ~/vopencv/bin/activate

#### others with python3.7

> cource ~/vweb/bin/activate

#### to exit venv

> deactivate

## 2. jupyter notebook

configured as a headless server, to start this service, enter the pytorch env first, then cd to a notebook dir like`~/Documents/course-v3`, then start the notebook with command`jupyter notebook`, the headless server will not open browser with token instead, and the port is shift from `8888` to `28888`, the notebook can be accessed by LAN users.

users will be asked to submit a password instead of using token while logging into the notebook.

the configuration files are in `~/jupyter/`

## 3. resources

#### fastai notebook

> ~/Documents/course-v3

#### paddle paddle models

> ~/Documents/models

#### CUDA check scripts

###### CUDA local check

`nvcc -c cuda_test.cu; gcc cuda_test.o -lcudart; ./a.out`

> ~/cuda_test.cu

###### CUDA tensorflow check

>(vtf) ~/gpu_check_tensorflow.py

###### CUDA torch check

>(vfastai) ~/gpu_check_torch.py
