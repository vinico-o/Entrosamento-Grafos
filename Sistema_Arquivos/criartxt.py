import pandas as pd

inputfile = "archive/database.csv"
jogadores = "archive/jogadores.txt"
times = "archive/times.txt"
nacionalidades = "archive/nacionalidades.txt"
posicoes = "archive/posicoes.txt"

with open(inputfile, "r", encoding="utf-8") as csvfile, \
    open(jogadores, "w", encoding="utf-8") as txtfile, \
    open(times, "w", encoding="utf-8") as txtfile, \
    open(nacionalidades, "w", encoding="utf-8") as txtfile, \
    open(posicoes, "w", encoding="utf-8") as txtfile:

        df = pd.read_csv(inputfile)
        jogador = df["Jogador"]
        time = df["Time"]
        nacao = df["Nação"]
        posicao = df["Pos."]

        jogador.to_csv(jogadores, sep='\t', index=False)
        time.to_csv(times, sep='\t', index=False)
        nacao.to_csv(nacionalidades, sep='\t', index=False)
        posicao.to_csv(posicoes, sep='\t', index=False)


         



