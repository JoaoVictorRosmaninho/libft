# 📋 libft Tasks Index

Este diretório contém a documentação de melhorias e tasks para o projeto libft.

## 📌 Tasks Ativas

### [TASK_001: Arena Allocator - Robustez e Idempotência](./TASK_001_ARENA_ROBUSTNESS.md)

**Status:** ⏳ Pendente  
**Prioridade:** 🔴 Alta  
**Complexidade:** 🟡 Média  
**Estimativa:** 8-12 horas

**Descrição Breve:**
Implementar um sistema robusto de gerenciamento de ciclo de vida para o Arena Allocator, incluindo:
- State machine para controle explícito de estados
- Idempotência em funções de cleanup
- Remoção de side effects ocultos
- Ownership model documentado
- Testes abrangentes

**O Que Foi Descoberto:**
- Double-free em `ft_arena_destroy()` causado por falta de proteção
- Side effects ocultos em `ft_printf()` que destroem globalmente
- Falta de estado visível no ciclo de vida de arenas
- Contrato implícito entre componentes

**Arquivos Relacionados:**
- [TASK_001_ARENA_ROBUSTNESS.md](./TASK_001_ARENA_ROBUSTNESS.md) - Documentação completa
- [IMPLEMENTATION_EXAMPLES.md](./IMPLEMENTATION_EXAMPLES.md) - Exemplos de código
- Modificar: `libs/libft/includes/arena.h`
- Modificar: `libs/libft/src/memory/arena_utils.c`
- Modificar: `libs/libft/src/memory/arena.c`
- Criar: `libs/libft/test/arena_robustness_test.c`

**Quick Start:**
```bash
# 1. Revisar documento
cat TASK_001_ARENA_ROBUSTNESS.md

# 2. Revisar exemplos
cat IMPLEMENTATION_EXAMPLES.md

# 3. Começar implementação (phase by phase)
# Ver timeline na TASK_001
```

---

## 🔍 Padrões de Design Referenciados

### State Pattern (Gang of Four)
- Implementar state machine explícito
- Transições definidas entre UNINITIALIZED → ACTIVE → DESTROYED
- Ver: TASK_001, seção "Objective 1"

### Idempotence
- Operações seguras para chamar múltiplas vezes
- Ver: TASK_001, seção "Objective 2"
- Referência: RFC 7231 (HTTP Semantics)

### RAII - Resource Acquisition Is Initialization
- Ciclo de vida ligado ao escopo
- Ver: TASK_001, seção "Referências - RAII"
- Implementação em C com `__attribute__((cleanup))`

### Design by Contract
- Precondições, postcondições, invariantes
- Ver: TASK_001, seção "Referências - Invariants"
- Usar assertions para validar

### Defensive Programming
- Verificações de NULL
- Validação de estado
- Proteção contra uso indevido
- Ver: TASK_001, seção "Referências - Defensive"

---

## 📚 Documentos Suplementares

| Documento | Propósito |
|-----------|----------|
| [TASK_001_ARENA_ROBUSTNESS.md](./TASK_001_ARENA_ROBUSTNESS.md) | Especificação completa da task |
| [IMPLEMENTATION_EXAMPLES.md](./IMPLEMENTATION_EXAMPLES.md) | Exemplos práticos de código |
| [OWNERSHIP_MODEL.md](./IMPLEMENTATION_EXAMPLES.md#5-ownership-documentation-template) | Modelo de propriedade de recursos |

---

## 🎯 Objetivos por Task

### TASK_001 Objetivos:

1. ✅ **[DONE]** Implementar enum `t_arena_state` 
2. ⏳ **[PENDING]** State machine com transições definidas
3. ⏳ **[PENDING]** `ft_arena_destroy()` idempotente
4. ⏳ **[PENDING]** `ft_arena_validate()` com verificação de invariantes
5. ⏳ **[PENDING]** Remover side effects de `ft_printf()`
6. ⏳ **[PENDING]** Ownership model documentado
7. ⏳ **[PENDING]** Test suite completo (5+ suites)
8. ⏳ **[PENDING]** Valgrind 100% limpo
9. ⏳ **[PENDING]** Documentação no código

---

## 💡 Lessons Learned

### Do Erro ao Design

**Problema:** Double-free em `ft_arena_destroy()`

**Causa Raiz:**
- Falta de idempotência
- Sem verificação de estado
- Side effects ocultos em `ft_printf()`

**Solução:**
- State machine explícito
- Proteção contra chamadas múltiplas
- Cleanup explícito (não implícito)

**Moral:** 
> "Em C, a liberdade vem com responsabilidade. 
> Sempre documente contratos, valide estado,
> e torne funções defensivas."

---

## 📖 Referências Externas

### Livros Clássicos
1. "The C Programming Language" - K&R (1988)
2. "Design Patterns" - Gang of Four (1994)
3. "Code Complete" - Steve McConnell (2004)
4. "The Pragmatic Programmer" - Hunt & Thomas (2019)

### Documentos Online
- https://en.wikipedia.org/wiki/Idempotence
- https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html
- RFC 7231: HTTP Semantics

### Padrões Relacionados
- State Pattern
- Singleton Pattern
- RAII Pattern
- Factory Pattern
- Resource Management

---

## 🔧 Workflow Recomendado

### Para Implementar TASK_001:

1. **Leitura** (1h)
   - Ler `TASK_001_ARENA_ROBUSTNESS.md` completamente
   - Revisar exemplos em `IMPLEMENTATION_EXAMPLES.md`

2. **Design** (1h)
   - Esboçar diagramas de estado
   - Identificar todos os pontos de mudança

3. **Implementação** (6h)
   - Fase por fase (ver timeline em TASK_001)
   - Commit após cada fase
   - Testar continuamente

4. **Testes** (2h)
   - Executar test suites
   - Valgrind com leak check
   - Edge cases

5. **Documentação** (1h)
   - Comentar código
   - Atualizar README
   - Exemplos de uso

---

## ✅ Definition of Done

Um task é considerado "done" quando:

- [ ] Todos os objetivos implementados
- [ ] Todos os testes passando
- [ ] Valgrind 100% limpo
- [ ] Documentação completa
- [ ] Code review aprovado
- [ ] Exemplos funcionando
- [ ] Nenhuma regressão

---

## 📞 Suporte

Para dúvidas durante implementação:

1. **Revisar exemplos** - `IMPLEMENTATION_EXAMPLES.md`
2. **Consultar padrões** - Seção de referências em `TASK_001`
3. **Executar testes** - Validar incrementalmente
4. **Valgrind** - Verificar memory safety

---

## 🗂️ Estrutura do Diretório

```
tasks/
├── README.md (este arquivo)
├── TASK_001_ARENA_ROBUSTNESS.md
├── IMPLEMENTATION_EXAMPLES.md
└── [future tasks]
```

---

**Última Atualização:** 6 de dezembro de 2025  
**Próxima Review:** Após completar TASK_001  
**Status Geral:** 1 task ativa, pronta para implementação
