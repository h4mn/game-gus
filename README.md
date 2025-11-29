# Game Gus - Roguelike Terminal

Um jogo de aventura e exploração em terminal desenvolvido em C por Gustavo Secco, Gustavo Silva, Luiz Saia e Vinícius Heleno.

## 🎮 Gameplay

O jogador se encontra em um lugar escuro com uma espada desgastada e precisa:

1. **Explorar o mapa** (15×15) com visão limitada
2. **Encontrar o baú (@)** para pegar tocha e poção de cura
3. **Enfrentar o monstro (M)** que persegue o jogador
4. **Derrotar o monstro** para obter a chave
5. **Usar a chave** na porta (O) para escapar

## 🎯 Objetivo

Encontrar a saída do lugar misterioso antes que o monstro derrote o jogador ou a tocha apague.

## 🕹️ Controles

```
[W] [A] [S] [D] | [Q]uit > █
```

- **W/A/S/D:** Movimento (cima/esquerda/baixo/direita)
- **Q:** Sair do jogo (com confirmação)

## 🗺️ Elementos do Mapa

| Símbolo | Descrição |
|----------|------------|
| **P** | Jogador (Player) |
| **M** | Monstro (persegue quando próximo) |
| **@** | Baú (tocha + cura) |
| **O** | Porta (requer chave) |
| **#** | Paredes |
| **.** | Chão visível |
| ** ** | Escuridão (fora da visão) |

## ❤️ Sistema de Vida

- **3 HP:** █ █ █ (cheio)
- **2 HP:** █ █ ░ (danificado)
- **1 HP:** █ ░ ░ (crítico)
- **0 HP:** ░ ░ ░ (game over)

## 🔥 Sistema de Tocha

- **Duração:** 100 turnos
- **Efeito:** Aumenta visão de 2→5 células
- **Feedback:** "Sua tocha apagou!" quando acaba

## 👾 IA do Monstro

- **Perseguição:** Ativa quando jogador está na visão
- **Movimento:** 2 turnos quando próximo, 4 turnos quando distante
- **Dano:** Causa 1 HP por colisão
- **Drop:** Chave quando derrotado

## 🏗️ Arquitetura Técnica

### Estrutura do Código
- ** Linguagem:** C ANSI
- **Compilação:** `gcc game-gus.c -o game.exe`
- **Dependências:** `stdio.h`, `stdlib.h`, `time.h`, `conio.h`
- **Plataforma:** Windows (CMD/PowerShell)

### Sistema de Renderização
- **Viewport:** 15×15 células com bordas
- **Visão dinâmica:** Baseada em distância do jogador
- **HUD otimizada:** 25 linhas totais (jogo + interface)
- **Input responsivo:** Sem necessidade de Enter

## ✨ Melhorias Implementadas

### 🎨 Interface Profissional
- **Encoding UTF-8:** Correção de caracteres acentuados
- **Input responsivo:** `getch()` sem necessidade de Enter
- **HUD unificada:** Barra de comandos integrada
- **Botões visuais:** `[W] [A] [S] [D] | [Q]uit`

### 🧠 Experiência Otimizada
- **Help integrado:** Sempre visível na interface
- **Feedback visual:** Indicadores claros de HP e estado
- **Sistema de dicas:** Contextuais e não intrusivas
- **Controle de fluxo:** Evita loops desnecessários

### 🔧 Compatibilidade
- **ASCII-safe:** Caracteres compatíveis com Windows CMD
- **Memory-safe:** Validação de limites de array
- **Input robusto:** Tratamento de comandos inválidos
- **Performance:** Renderização otimizada para terminal

## 🚀 Como Compilar e Executar

```bash
# Compilação
gcc game-gus.c -o game.exe

# Execução
./game.exe
```

## 🔮 Possíveis Expansões

- [ ] Múltiplos níveis com dificuldade crescente
- [ ] Sistema de inventário com itens diversos
- [ ] Tipos diferentes de monstros com IA variada
- [ ] Mecânicas de furtividade e surpresa
- [ ] Sistema de pontuação baseado em tempo e HP restante
- [ ] Modo hardcore com perma-morte

## 📝 Créditos

**Desenvolvimento Original:** Gustavo Secco, Gustavo Silva, Luiz Saia, Vinícius Heleno
**Lead Developer:** Hadston Nunes
**Otimizações e Interface:** Sky (Agente de Desenvolvimento)
**Versão:** 0.0.12 (Otimizado)

> "Simplicidade funcional é a essência dos grandes jogos clássicos." – made by Sky 🎮