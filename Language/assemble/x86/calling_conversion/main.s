
a.out:     file format elf64-x86-64


Disassembly of section .init:

00000000004003f0 <_init>:
  4003f0:	48 83 ec 08          	sub    $0x8,%rsp
  4003f4:	48 8b 05 fd 0b 20 00 	mov    0x200bfd(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  4003fb:	48 85 c0             	test   %rax,%rax
  4003fe:	74 05                	je     400405 <_init+0x15>
  400400:	e8 3b 00 00 00       	callq  400440 <__libc_start_main@plt+0x10>
  400405:	48 83 c4 08          	add    $0x8,%rsp
  400409:	c3                   	retq   

Disassembly of section .plt:

0000000000400410 <__stack_chk_fail@plt-0x10>:
  400410:	ff 35 f2 0b 20 00    	pushq  0x200bf2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400416:	ff 25 f4 0b 20 00    	jmpq   *0x200bf4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40041c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400420 <__stack_chk_fail@plt>:
  400420:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400426:	68 00 00 00 00       	pushq  $0x0
  40042b:	e9 e0 ff ff ff       	jmpq   400410 <_init+0x20>

0000000000400430 <__libc_start_main@plt>:
  400430:	ff 25 ea 0b 20 00    	jmpq   *0x200bea(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400436:	68 01 00 00 00       	pushq  $0x1
  40043b:	e9 d0 ff ff ff       	jmpq   400410 <_init+0x20>

Disassembly of section .plt.got:

0000000000400440 <.plt.got>:
  400440:	ff 25 b2 0b 20 00    	jmpq   *0x200bb2(%rip)        # 600ff8 <_DYNAMIC+0x1d0>
  400446:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400450 <_start>:
  400450:	31 ed                	xor    %ebp,%ebp
  400452:	49 89 d1             	mov    %rdx,%r9
  400455:	5e                   	pop    %rsi
  400456:	48 89 e2             	mov    %rsp,%rdx
  400459:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40045d:	50                   	push   %rax
  40045e:	54                   	push   %rsp
  40045f:	49 c7 c0 60 06 40 00 	mov    $0x400660,%r8
  400466:	48 c7 c1 f0 05 40 00 	mov    $0x4005f0,%rcx
  40046d:	48 c7 c7 84 05 40 00 	mov    $0x400584,%rdi
  400474:	e8 b7 ff ff ff       	callq  400430 <__libc_start_main@plt>
  400479:	f4                   	hlt    
  40047a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400480 <deregister_tm_clones>:
  400480:	b8 3f 10 60 00       	mov    $0x60103f,%eax
  400485:	55                   	push   %rbp
  400486:	48 2d 38 10 60 00    	sub    $0x601038,%rax
  40048c:	48 83 f8 0e          	cmp    $0xe,%rax
  400490:	48 89 e5             	mov    %rsp,%rbp
  400493:	76 1b                	jbe    4004b0 <deregister_tm_clones+0x30>
  400495:	b8 00 00 00 00       	mov    $0x0,%eax
  40049a:	48 85 c0             	test   %rax,%rax
  40049d:	74 11                	je     4004b0 <deregister_tm_clones+0x30>
  40049f:	5d                   	pop    %rbp
  4004a0:	bf 38 10 60 00       	mov    $0x601038,%edi
  4004a5:	ff e0                	jmpq   *%rax
  4004a7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  4004ae:	00 00 
  4004b0:	5d                   	pop    %rbp
  4004b1:	c3                   	retq   
  4004b2:	0f 1f 40 00          	nopl   0x0(%rax)
  4004b6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004bd:	00 00 00 

00000000004004c0 <register_tm_clones>:
  4004c0:	be 38 10 60 00       	mov    $0x601038,%esi
  4004c5:	55                   	push   %rbp
  4004c6:	48 81 ee 38 10 60 00 	sub    $0x601038,%rsi
  4004cd:	48 c1 fe 03          	sar    $0x3,%rsi
  4004d1:	48 89 e5             	mov    %rsp,%rbp
  4004d4:	48 89 f0             	mov    %rsi,%rax
  4004d7:	48 c1 e8 3f          	shr    $0x3f,%rax
  4004db:	48 01 c6             	add    %rax,%rsi
  4004de:	48 d1 fe             	sar    %rsi
  4004e1:	74 15                	je     4004f8 <register_tm_clones+0x38>
  4004e3:	b8 00 00 00 00       	mov    $0x0,%eax
  4004e8:	48 85 c0             	test   %rax,%rax
  4004eb:	74 0b                	je     4004f8 <register_tm_clones+0x38>
  4004ed:	5d                   	pop    %rbp
  4004ee:	bf 38 10 60 00       	mov    $0x601038,%edi
  4004f3:	ff e0                	jmpq   *%rax
  4004f5:	0f 1f 00             	nopl   (%rax)
  4004f8:	5d                   	pop    %rbp
  4004f9:	c3                   	retq   
  4004fa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400500 <__do_global_dtors_aux>:
  400500:	80 3d 31 0b 20 00 00 	cmpb   $0x0,0x200b31(%rip)        # 601038 <__TMC_END__>
  400507:	75 11                	jne    40051a <__do_global_dtors_aux+0x1a>
  400509:	55                   	push   %rbp
  40050a:	48 89 e5             	mov    %rsp,%rbp
  40050d:	e8 6e ff ff ff       	callq  400480 <deregister_tm_clones>
  400512:	5d                   	pop    %rbp
  400513:	c6 05 1e 0b 20 00 01 	movb   $0x1,0x200b1e(%rip)        # 601038 <__TMC_END__>
  40051a:	f3 c3                	repz retq 
  40051c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400520 <frame_dummy>:
  400520:	bf 20 0e 60 00       	mov    $0x600e20,%edi
  400525:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400529:	75 05                	jne    400530 <frame_dummy+0x10>
  40052b:	eb 93                	jmp    4004c0 <register_tm_clones>
  40052d:	0f 1f 00             	nopl   (%rax)
  400530:	b8 00 00 00 00       	mov    $0x0,%eax
  400535:	48 85 c0             	test   %rax,%rax
  400538:	74 f1                	je     40052b <frame_dummy+0xb>
  40053a:	55                   	push   %rbp
  40053b:	48 89 e5             	mov    %rsp,%rbp
  40053e:	ff d0                	callq  *%rax
  400540:	5d                   	pop    %rbp
  400541:	e9 7a ff ff ff       	jmpq   4004c0 <register_tm_clones>

0000000000400546 <sum>:
  400546:	55                   	push   %rbp
  400547:	48 89 e5             	mov    %rsp,%rbp
  40054a:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40054d:	89 75 f8             	mov    %esi,-0x8(%rbp)
  400550:	89 55 f4             	mov    %edx,-0xc(%rbp)
  400553:	89 4d f0             	mov    %ecx,-0x10(%rbp)
  400556:	44 89 45 ec          	mov    %r8d,-0x14(%rbp)
  40055a:	44 89 4d e8          	mov    %r9d,-0x18(%rbp)
  40055e:	8b 55 fc             	mov    -0x4(%rbp),%edx
  400561:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400564:	01 c2                	add    %eax,%edx
  400566:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400569:	01 c2                	add    %eax,%edx
  40056b:	8b 45 f0             	mov    -0x10(%rbp),%eax
  40056e:	01 c2                	add    %eax,%edx
  400570:	8b 45 ec             	mov    -0x14(%rbp),%eax
  400573:	01 c2                	add    %eax,%edx
  400575:	8b 45 e8             	mov    -0x18(%rbp),%eax
  400578:	01 c2                	add    %eax,%edx
  40057a:	48 8b 45 10          	mov    0x10(%rbp),%rax
  40057e:	8b 00                	mov    (%rax),%eax
  400580:	01 d0                	add    %edx,%eax
  400582:	5d                   	pop    %rbp
  400583:	c3                   	retq   

0000000000400584 <main>:
  400584:	55                   	push   %rbp
  400585:	48 89 e5             	mov    %rsp,%rbp
  400588:	48 83 ec 10          	sub    $0x10,%rsp
  40058c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400593:	00 00 
  400595:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  400599:	31 c0                	xor    %eax,%eax
  40059b:	c7 45 f4 07 00 00 00 	movl   $0x7,-0xc(%rbp)
  4005a2:	48 8d 45 f4          	lea    -0xc(%rbp),%rax
  4005a6:	50                   	push   %rax
  4005a7:	41 b9 06 00 00 00    	mov    $0x6,%r9d
  4005ad:	41 b8 05 00 00 00    	mov    $0x5,%r8d
  4005b3:	b9 04 00 00 00       	mov    $0x4,%ecx
  4005b8:	ba 03 00 00 00       	mov    $0x3,%edx
  4005bd:	be 02 00 00 00       	mov    $0x2,%esi
  4005c2:	bf 01 00 00 00       	mov    $0x1,%edi
  4005c7:	e8 7a ff ff ff       	callq  400546 <sum>
  4005cc:	48 83 c4 08          	add    $0x8,%rsp
  4005d0:	b8 00 00 00 00       	mov    $0x0,%eax
  4005d5:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  4005d9:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  4005e0:	00 00 
  4005e2:	74 05                	je     4005e9 <main+0x65>
  4005e4:	e8 37 fe ff ff       	callq  400420 <__stack_chk_fail@plt>
  4005e9:	c9                   	leaveq 
  4005ea:	c3                   	retq   
  4005eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004005f0 <__libc_csu_init>:
  4005f0:	41 57                	push   %r15
  4005f2:	41 56                	push   %r14
  4005f4:	41 89 ff             	mov    %edi,%r15d
  4005f7:	41 55                	push   %r13
  4005f9:	41 54                	push   %r12
  4005fb:	4c 8d 25 0e 08 20 00 	lea    0x20080e(%rip),%r12        # 600e10 <__frame_dummy_init_array_entry>
  400602:	55                   	push   %rbp
  400603:	48 8d 2d 0e 08 20 00 	lea    0x20080e(%rip),%rbp        # 600e18 <__init_array_end>
  40060a:	53                   	push   %rbx
  40060b:	49 89 f6             	mov    %rsi,%r14
  40060e:	49 89 d5             	mov    %rdx,%r13
  400611:	4c 29 e5             	sub    %r12,%rbp
  400614:	48 83 ec 08          	sub    $0x8,%rsp
  400618:	48 c1 fd 03          	sar    $0x3,%rbp
  40061c:	e8 cf fd ff ff       	callq  4003f0 <_init>
  400621:	48 85 ed             	test   %rbp,%rbp
  400624:	74 20                	je     400646 <__libc_csu_init+0x56>
  400626:	31 db                	xor    %ebx,%ebx
  400628:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40062f:	00 
  400630:	4c 89 ea             	mov    %r13,%rdx
  400633:	4c 89 f6             	mov    %r14,%rsi
  400636:	44 89 ff             	mov    %r15d,%edi
  400639:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40063d:	48 83 c3 01          	add    $0x1,%rbx
  400641:	48 39 eb             	cmp    %rbp,%rbx
  400644:	75 ea                	jne    400630 <__libc_csu_init+0x40>
  400646:	48 83 c4 08          	add    $0x8,%rsp
  40064a:	5b                   	pop    %rbx
  40064b:	5d                   	pop    %rbp
  40064c:	41 5c                	pop    %r12
  40064e:	41 5d                	pop    %r13
  400650:	41 5e                	pop    %r14
  400652:	41 5f                	pop    %r15
  400654:	c3                   	retq   
  400655:	90                   	nop
  400656:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40065d:	00 00 00 

0000000000400660 <__libc_csu_fini>:
  400660:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400664 <_fini>:
  400664:	48 83 ec 08          	sub    $0x8,%rsp
  400668:	48 83 c4 08          	add    $0x8,%rsp
  40066c:	c3                   	retq   
