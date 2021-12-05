# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file
    with open(sys.argv[1], "r") as file:  # open csv file for reading
        reader = csv.DictReader(file)  # instantiate reader
        for row in reader:  # read each row
            row["rating"] = int(row["rating"])  # convert str to int type
            teams.append(row)  # add each team to teams list

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)  # identify the winner
        if winner in counts:  # if winner exists in counts dictionary
            counts[winner] += 1  # simply increment its value
        else:  # if not
            counts[winner] = 1  # create key with the name of winner and value with 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) != 1:  # repeat until only one team is left
        teams = simulate_round(teams)  # reassign teams to the result of simulate_round finction (returns winners)
    
    return teams[0]["team"]  # return the name of the winner


if __name__ == "__main__":
    main()
