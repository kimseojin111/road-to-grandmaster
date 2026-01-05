#!/usr/bin/env python3
import pandas as pd
import random
import argparse

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", default="agc.csv", help="CSV file (default: agc.csv)")
    ap.add_argument("--min", type=int, required=True, help="minimum difficulty")
    ap.add_argument("--max", type=int, required=True, help="maximum difficulty")
    args = ap.parse_args()

    df = pd.read_csv(args.csv)

    # filter rows with valid difficulty
    filt = df["difficulty"].apply(lambda x: pd.notnull(x))
    df = df[filt]

    # cast to int
    df["difficulty"] = df["difficulty"].astype(int)

    # range filter
    subset = df[(df["difficulty"] >= args.min) & (df["difficulty"] <= args.max)]

    if subset.empty:
        print("No problems found in that range.")
        return

    row = subset.sample(n=1).iloc[0]
    print("🎯 Selected Problem:")
    print(f"- Contest: {row['contest_id']}")
    print(f"- Problem: {row['problem_id']} {row['title']}")
    print(f"- Difficulty: {row['difficulty']}")
    print(f"- Link: {row['url']}")

if __name__ == "__main__":
    main()
