# 🧪 Controle e Dosagem em Tanques de Fluidos (Batelada)

Sistema de automação e monitoramento de pH para tanques industriais de processamento em batelada, desenvolvido para indústrias químicas, alimentícias e de saneamento.

Este repositório contém duas implementações complementares do sistema:
1. **Versão em Python:** Simulação de telemetria contínua, amostragem automatizada e validação por média de lote.
2. **Versão em C:** Controle de baixo nível com alocação dinâmica de memória, intertravamento de segurança (*Safety Interlock*) por sensor individual e gerenciamento de atuadores.

---

## 📌 Visão Geral do Processo

Em processos industriais por batelada, a conformidade do pH é crítica para a qualidade do produto e segurança operacional. O sistema monitora uma planta com **$N$ tanques**, onde cada tanque possui **$M$ sensores de pH** instalados em redundância.

- **Faixa de Tolerância do pH:** `6.5` a `7.5`
- **Operação Normal:** Se o produto estiver em conformidade, a válvula de escoamento é aberta para liberação da batelada.
- **Operação de Falha:** Se houver desvio, o sistema bloqueia o escoamento, aciona a recirculação e dispara o alarme químico/crítico.

---

## 🛠️ Comparativo das Implementações

| Recurso | Versão Python (`main.py`) | Versão C (`main.c`) |
| :--- | :--- | :--- |
| **Foco** | Simulação e validação de alto nível | Controle embarcado e gerenciamento de memória |
| **Entrada de Dados** | Telemetria simulada via `random` | Entrada de dados via console/teclado |
| **Lógica de Validação** | Avaliação baseada na **média** do tanque | Avaliação por **sensor individual** (Triagem estrita) |
| **Gestão de Memória** | Gerenciada dinamicamente pelo interpretador | Manual via `malloc`, `free` e navegação por ponteiros |
| **Modo de Execução** | Loop contínuo com temporizador (`time.sleep`) | Execução ciclo a ciclo com liberação de RAM |

---

## ⚙️ Parâmetros do Sistema

- **Quantidade de Tanques:** 4
- **Sensores por Tanque:** 3 (Redundância de leitura)
- **pH Mínimo Permitido:** `6.5`
- **pH Máximo Permitido:** `7.5`

---
