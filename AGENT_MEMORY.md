# Memória do Agente - Game Gus

## 🎯 Contexto do Projeto
- **Repositório:** Hadsteca → workspaces → legacy → c
- **Arquivo principal:** `game-gus.c`
- **Tipo:** Roguelike terminal em C ANSI
- **Objetivo:** Jogo de exploração com mecânicas simples mas envolventes

## 🛠️ Melhorias Implementadas (Sessão 1)

### Encoding e Compatibilidade
- **Problema:** Arquivo em Windows-1252 com caracteres corrompidos
- **Solução:** Conversão para UTF-8 + caracteres ASCII-safe
- **Resultado:** Interface limpa e compatível

### Sistema de Input
- **Problema:** `scanf()` exigia Enter após cada comando
- **Solução:** `getch()` com input instantâneo
- **Resultado:** Gameplay fluido e responsivo

### Interface/HUD
- **Problema:** Espaço desperdiçado e informações redundantes
- **Solução:** HUD unificada em 25 linhas totais
- **Evolução:** Texto separado → Barra com borders → Botões visuais
- **Resultado:** Interface profissional e economizada

### Fluxo de Comandos
- **Problema:** Help condicional, prompts redundantes
- **Solução:** Controles sempre visíveis, help opcional removido
- **Resultado:** Experiência intuitiva e sem ruído

## 🎮 Design Patterns Aplicados

### Renderização Otimizada
- **Viewport fixo:** 15×15 com sistema de visão dinâmica
- **Limitação vertical:** 25 linhas totais (jogo + HUD)
- **Backward compatibility:** Caracteres ASCII para Windows CMD

### Input Responsivo
- **Single-key:** Input sem buffer de Enter
- **Visual feedback:** Botões estilizados como `[W] [A] [S] [D]`
- **Error handling:** Comandos inválidos não quebram ritmo

### Experiência de Usuário
- **Progressive disclosure:** Informações aparecem conforme necessário
- **Consistency:** Elementos visuais consistentes (HP, controles)
- **Minimalismo:** Cada elemento tem propósito claro

## 🔧 Arquitetura de Decisões

### Por que 15×15?
- **Razão:** Equilíbrio entre explorabilidade e performance
- **Viewport:** Cabe confortavelmente em terminal padrão (80x25)
- **Gameplay:** Suficiente para estratégia sem ser sobrecarregante

### Por que ASCII-safe?
- **Problema:** Windows CMD não renderiza Unicode consistentemente
- **Solução:** Caracteres padrão ASCII (219, 176, 219, etc.)
- **Benefício:** Funciona em qualquer ambiente Windows

### Por que input sem Enter?
- **Problema:** `scanf()` cria fricção desnecessária
- **Solução:** `getch()` para input instantâneo
- **Resultado:** Gameplay mais fluido e moderno

## 🚀 Próximos Passos (Futuras Expansões)

### Sistema de Níveis
- [ ] Procedural generation de mapas
- [ ] Sistema de dificuldade progressiva
- [ ] Save/load de jogo

### Mecânicas Avançadas
- [ ] Inventário com múltiplos itens
- [ ] Status effects (poções, buffs)
- [ ] Tipos de武器 com diferentes danos

### IA Melhorada
- [ ] Pathfinding A* para monstro
- [ ] Sistema de patrulha
- [ ] Boss fights com mecânicas especiais

## 💡 Insights Técnicos

### Otimização de Renderização
- **Double buffering:** Limpar tela apenas quando necessário
- **Viewport culling:** Renderizar apenas células visíveis
- **Char cache:** Pré-computar strings de HP

### Memory Management
- **Stack allocation:** Variáveis locais no stack
- **Bounds checking:** Validar acesso a arrays
- **Resource cleanup:** Liberar recursos ao sair

## 🎯 Lembretes para Futuras Sessões

1. **Manter compatibilidade:** Sempre testar em Windows CMD
2. **Preservar simplicidade:** Não adicionar complexidade desnecessária
3. **Documentar mudanças:** Atualizar README.md
4. **Testar boundary cases:** Bordas, input inválido, extremos
5. **Performance Considerations:** Terminal tem limitações de renderização

## 📊 Estado Atual do Projeto

- **Versão:** 0.0.1 (Otimizado)
- **Status:** Funcional e documentado
- **Próximo passo:** Aguardar feedback para novas features
- **Artefatos:** README.md, AGENT_MEMORY.md, game-gus.c

> "Memória não é sobre lembrar o passado, é sobre construir melhor no futuro." – made by Sky 🧠