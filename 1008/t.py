#!/usr/bin/env python3
# agc_table.py
# Build an AGC problems table sorted by difficulty using AtCoderProblems data.
# Fixes 403 errors by sending a proper User-Agent and using requests with retries.

import argparse, csv, json, sys, time
from typing import Any, Dict, List, Optional, Tuple

try:
    import requests
except ImportError:
    print("Please `pip install requests`", file=sys.stderr)
    sys.exit(1)

# Primary (static) endpoints
CONTESTS_URL = "https://kenkoooo.com/atcoder/resources/contests.json"
PROBLEMS_URL = "https://kenkoooo.com/atcoder/resources/problems.json"
MODELS_URL   = "https://kenkoooo.com/atcoder/resources/problem-models.json"

# Fallback API endpoints (slower but useful if static endpoints are blocked)
FALLBACK_CONTESTS_URL = "https://kenkoooo.com/atcoder/atcoder-api/v3/contests"
FALLBACK_PROBLEMS_URL = "https://kenkoooo.com/atcoder/atcoder-api/v3/problems"
# problem models fallback (community mirror of the same data)
FALLBACK_MODELS_URL   = MODELS_URL  # the API provides models via the same path

HEADERS = {
    "User-Agent": "AGC-Table-Script/1.0 (+https://atcoder.jp/) requests",
    "Accept": "application/json",
    "Connection": "keep-alive",
}

def fetch_json(url: str, timeout: float = 20.0, max_retries: int = 3, sleep_sec: float = 1.5) -> Any:
    last_exc: Optional[Exception] = None
    for i in range(max_retries):
        try:
            r = requests.get(url, headers=HEADERS, timeout=timeout)
            if r.status_code == 200:
                return r.json()
            # Retry on 403/429/5xx
            if r.status_code in (403, 429) or 500 <= r.status_code < 600:
                time.sleep(sleep_sec * (i + 1))
                continue
            r.raise_for_status()
        except Exception as e:
            last_exc = e
            time.sleep(sleep_sec * (i + 1))
    if last_exc:
        raise last_exc
    raise RuntimeError(f"Failed to fetch {url}")

def load_contests() -> List[Dict[str, Any]]:
    try:
        return fetch_json(CONTESTS_URL)
    except Exception:
        return fetch_json(FALLBACK_CONTESTS_URL)

def load_problems() -> List[Dict[str, Any]]:
    try:
        return fetch_json(PROBLEMS_URL)
    except Exception:
        return fetch_json(FALLBACK_PROBLEMS_URL)

def load_models() -> Dict[str, Dict[str, Any]]:
    # models endpoint returns a dict keyed by problem_id
    try:
        data = fetch_json(MODELS_URL)
        if isinstance(data, dict):
            return data
        # some mirrors may return list; normalize to dict if needed
        if isinstance(data, list):
            return {d.get("id") or d.get("problem_id"): d for d in data if isinstance(d, dict)}
        return {}
    except Exception:
        data = fetch_json(FALLBACK_MODELS_URL)
        if isinstance(data, dict):
            return data
        if isinstance(data, list):
            return {d.get("id") or d.get("problem_id"): d for d in data if isinstance(d, dict)}
        return {}

def build_rows(order: str, limit: int) -> List[Dict[str, Any]]:
    contests = load_contests()
    problems = load_problems()
    models   = load_models()

    agc_ids = {c["id"] for c in contests if str(c.get("id","")).lower().startswith("agc")}

    rows: List[Dict[str, Any]] = []
    for p in problems:
        cid = p.get("contest_id", "")
        if cid not in agc_ids:
            continue
        pid = p.get("id", "")
        title = p.get("title", "")
        m = models.get(pid, {}) if isinstance(models, dict) else {}
        diff = m.get("difficulty", None)
        exp  = bool(m.get("is_experimental", False))
        url  = f"https://atcoder.jp/contests/{cid}/tasks/{pid}"
        rows.append({
            "contest_id": cid,
            "problem_id": pid,
            "title": title,
            "difficulty": diff,
            "is_experimental": exp,
            "url": url
        })

    def sort_key(r: Dict[str, Any]) -> Tuple[int, float]:
        d = r["difficulty"]
        return (1, float("inf")) if d is None else (0, float(d))

    rows.sort(key=sort_key, reverse=(order == "desc"))
    if limit > 0:
        rows = rows[:limit]
    return rows

def print_markdown(rows: List[Dict[str, Any]]) -> None:
    print("| # | Contest | Problem | Title | Difficulty | Exp? | Link |")
    print("|---:|:--------|:--------|:------|-----------:|:----:|:-----|")
    for i, r in enumerate(rows, 1):
        d = "—" if r["difficulty"] is None else str(r["difficulty"])
        exp = "Y" if r["is_experimental"] else ""
        print(f"| {i} | {r['contest_id']} | {r['problem_id']} | {r['title']} | {d} | {exp} | [open]({r['url']}) |")

def save_csv(rows: List[Dict[str, Any]], path: str) -> None:
    with open(path, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["contest_id","problem_id","title","difficulty","is_experimental","url"])
        w.writeheader()
        w.writerows(rows)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--order", choices=["asc", "desc"], default="asc")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--csv", type=str, default="")
    args = ap.parse_args()

    rows = build_rows(args.order, args.limit)
    print_markdown(rows)
    if args.csv:
        save_csv(rows, args.csv)

if __name__ == "__main__":
    main()
