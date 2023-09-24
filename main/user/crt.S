.section .text
.extern main
.extern quit
entry:
    // 中断调用create_process
    
    call main
    
    // 中断调用close_process

