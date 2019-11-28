import torch

if torch.cuda.is_available() :
    print('CUDA PASSED')
    i = torch.cuda.device_count()
    print('NUM of RIGS :', i)
    for ii in range(i):
        print('RIG', ii, ':', torch.cuda.get_device_name(ii))
    
    
else:
    print('NO GPU / CUDA ERROR')
