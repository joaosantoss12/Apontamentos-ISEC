﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Exercicio1
{
    class Utilizador
    {
        public string Nome { get; set; }
        public List<Tarefa> Tarefas = new List<Tarefa>();
        public Utilizador(string nome)
        {
            Nome = nome;
            Tarefas = new List<Tarefa>();
        }

        //adiciona tarefas ao utilizador
        public void AdicionaTarefa(Tarefa tarefa)
        {
            Tarefas.Add(tarefa);
        }

        //lista tarefas do utilizador
        public void ListaTarefas()
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                Console.WriteLine(Tarefas[i].Imprime());
            }
        }

        //lista tarefas em atraso
        public void ListaTarefasAtraso()
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].DataLimite < DateTime.Now)
                {
                    Console.WriteLine(Tarefas[i].Imprime());
                }

            }
        }

        //lista tarefas por prioridade
        public void ListaTarefasPrioridade(string prioridade)
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].Prioridade.ToString() == prioridade)
                    Console.WriteLine(Tarefas[i].Imprime());           
            }
            
        }
        
        //lista tarefas por categoria
        public void ListaTarefasCategoria(string categoria)
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].Categoria.ToString() == categoria)
                    Console.WriteLine(Tarefas[i].Imprime());
            }

        }

        //lista tarefas por estado
        public void ListaTarefasEstado(string estado)
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].Estado.ToString() == estado)
                    Console.WriteLine(Tarefas[i].Imprime());
            }
        }

        //remove tarefas concluidas
        public void RemoveTarefasConcluidas()
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].Estado.ToString() == "Concluida")
                    Tarefas.Remove(Tarefas[i]);
            }
            
        }

        //remove tarefas pessoais
        public void RemoveTarefasPessoais()
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if(Tarefas[i].Categoria.ToString() == "Pessoal")
                    Tarefas.Remove(Tarefas[i]);
            }
        }

        //remove tarefas com baixa prioridade
        public void RemoveTarefasBaixaPrioridade()
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if (Tarefas[i].Prioridade.ToString() == "Baixa")
                    Tarefas.Remove(Tarefas[i]);
            }

        }

        // remove uma certa tarefa
        public void RemoveTarefa(Tarefa tarefa)
        {
            for(var i = 0; i < Tarefas.Count; i++)
            {
                if(tarefa == Tarefas[i])
                {
                    Tarefas.Remove(Tarefas[i]);
                    break;
                }
            }
        }
    }
}
