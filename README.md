## Projetos de Arduino de Potenciômetro, Botão, Barra de LEDs e Interrupções

Este repositório contém arquivos de hardware e software para dois projetos baseados em Arduino: um **Sistema de Semáforos Inteligente** e um **Controlador de Elevador** com máquina de estados.

---

## 🚦 Projeto 1: Sistema de Semáforos Inteligente

Este projeto implementa um sistema de semáforos com ajuste dinâmico do tempo de verde baseado no fluxo de veículos da via principal, simulado por um potenciômetro, e inclui funcionalidade para travessia de pedestres.

### 💾 Arquivos de Software (Sketch Arduino)

| Arquivo | Descrição |
| :--- | :--- |
| `semaforo.ino` | Contém o código principal do projeto de semáforos. Ele define pinos para os LEDs dos semáforos (Vias A e B) e para o potenciômetro (`A0`). Implementa o cálculo dinâmico dos tempos de verde ($G_A$ e $G_B$) com base no valor lido do potenciômetro (`potValor`), utilizando a função `map` para escalonar a leitura de 0-1023 para a fração de $G_{Total}$. O ciclo de semáforos (Verde A, Amarelo A, Vermelho A/Vermelho B, Verde B, Amarelo B, Vermelho A/Vermelho B) é implementado com os tempos fixos de Amarelo (`Y=2`) e Vermelho (`X=2`). Inclui `attachInterrupt` para botões de pedestre (pinos 2 e 3). |

### 🛠️ Arquivos de Hardware e Especificações

| Arquivo | Descrição |
| :--- | :--- |
| `Semaforo parte2.jpeg` | Diagrama de circuito que mostra a conexão dos LEDs (semáforos) e componentes de entrada (potenciômetro e botões) a uma placa **Arduino UNO**. |
| `SistemaSemaforos_Parte_1.pdf` | Detalha a operação base do semáforo: dois semáforos (A e B) com um ciclo de sincronização definido pelos tempos $G_A$ (Verde A), $G_B$ (Verde B), $Y$ (Amarelo) e $X$ (Ambos Vermelhos). O tempo total do ciclo de verde é constante ($G_{Total} = G_A + G_B = 10s$ no exemplo). |
| `SistemaSemaforos_Parte_2.pdf` | Descreve a extensão do projeto com a inclusão de **semáforos e botões de pedestres**. O acionamento de um botão deve causar a transição para Verde dos semáforos de pedestres e Vermelho para os de veículos, mas só após o fim do ciclo corrente do veículo. |

---

## ⬆️ Projeto 2: Controlador de Elevador

Este projeto simula o controle de um elevador usando uma **Máquina de Estados (State Machine)**, implementada em um sketch Arduino, com diversos componentes de entrada (botões) e saída (LEDs e fita de LEDs).

### 💾 Arquivos de Software (Sketch Arduino)

| Arquivo | Descrição |
| :--- | :--- |
| `elevador.ino` | O código principal, que define a **Máquina de Estados** para o elevador. Define 10 estados de operação, incluindo `INOPERANTE`, `OCIOSO`, e estados de movimento/parada para subir (`MOVENDO_S`, `ESTACIONADO_S`, etc.) e descer (`MOVENDO_D`, `ESTACIONADO_D`, etc.). Utiliza entradas analógicas (`A0`, `A1`, `A2`, `A3`) para ler múltiplos botões através de diferentes valores de resistência (divisores de tensão). Implementa funções para transição entre estados (`estado_INOPERANTE`, `estado_OCIOSO`, etc.) e controle de LEDs de indicação (`ledOperante`, `ledPortas`, `ledEmergencia`). Utiliza a biblioteca `Adafruit_NeoPixel` para controlar uma fita de LEDs como indicador de andar (`fitaLedAndar` pino 13). |
| `indicador_de_força_com_barra_de_leds.ino` | Um arquivo relacionado a outro projeto (indicador de força com barra de LEDs), mas que ilustra o uso da biblioteca `Adafruit_NeoPixel` para acender LEDs sequencialmente, similar ao que seria usado para o indicador de posição do elevador. |

### 🛠️ Arquivos de Hardware e Especificações

| Arquivo | Descrição |
| :--- | :--- |
| `Hardware completo.pdf` / `Elevador-Completo.png.pdf` | Diagramas de circuito que mostram a conexão do hardware. O sistema inclui um **Arduino UNO** e vários protoboards com **botões e resistores** (provavelmente configurados como divisores de tensão para entradas analógicas) e uma **fita de LEDs** (indicador de posição).  |
| `ProjetoElevador.pdf` | Documentação do projeto do elevador: |
| | * [cite_start]**Hardware:** Visuais conceituais de como os componentes se relacionam no sistema: **Controlador (Arduino)**, **Indicador de Posição (Fita de LEDs)**, **Indicadores de Estado (LEDs)**, e conjuntos de **Botões** (para ir aos andares, subir/descer, fechar porta, ON/OFF, Emergência). |
| | * [cite_start]**Software (Estados):** Definição da Máquina de Estados, incluindo: **Eventos** (`ON`, `OFF`, `alinhamento`, `emergencia`, `demanda`, etc.), **Ações** (`marcar_destino`, `abrir_porta`, `mover_S`, etc.), e **Condições** (`ha_emergencia`, `ha_destino`, `ha_demanda_acima`, etc.). |
| | * **Diagrama de Estados:** Apresenta o diagrama UML completo da Máquina de Estados do elevador, com transições condicionais, eventos e ações de entrada/saída para cada estado. |

---
