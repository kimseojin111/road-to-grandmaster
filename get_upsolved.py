import requests
import time

def fetch_api_response(url):
    """
    주어진 URL에 대해 API 요청을 보냅니다.
    응답이 없거나 status가 'OK'가 아닐 경우 2초 후 재시도합니다.
    """
    while True:
        try:
            response = requests.get(url, timeout=10)
            data = response.json()
            if data.get("status") == "OK":
                return data
            else:
                print(f"Bad response from API: {data}. Retrying in 2 seconds...")
        except Exception as e:
            print(f"Exception occurred: {e}. Retrying in 2 seconds...")
        time.sleep(2)

def get_user_status(handle):
    """
    주어진 핸들의 모든 제출 정보를 반환합니다.
    API: https://codeforces.com/api/user.status?handle=<handle>
    """
    url = f"https://codeforces.com/api/user.status?handle={handle}"
    data = fetch_api_response(url)
    return data['result']

def get_problemset_problems():
    """
    전체 문제 목록을 반환합니다.
    API: https://codeforces.com/api/problemset.problems
    """
    url = "https://codeforces.com/api/problemset.problems"
    data = fetch_api_response(url)
    return data['result']['problems']

def main():
    # 사용자로부터 핸들 3개를 입력받습니다.
    handles = ['JinyeongAckerman','gs25','ZmkzOWYyOHcwdWo4cj']
    
    # 각 사용자별로 맞춘 문제(set)와 제출이 이루어진 contestId를 저장합니다.
    solved = {handle: set() for handle in handles}
    contest_submitted = set()
    
    for handle in handles:
        submissions = get_user_status(handle)
        for submission in submissions:
            contest_id = submission.get('contestId')
            if contest_id is None:
                continue  # gym이나 비대회 제출 건은 무시
            contest_submitted.add(contest_id)
            if submission.get('verdict') == 'OK':  # 맞은 제출인 경우
                prob = submission.get('problem')
                if prob:
                    # 문제를 대회번호와 index로 식별 (prob에 contestId가 없으면 submission의 contest_id 사용)
                    solved[handle].add((prob.get('contestId', contest_id), prob.get('index')))
    
    # 전체 문제목록을 한 번의 요청으로 받아옵니다.
    all_problems = get_problemset_problems()
    unsolved_problems = []
    
    # 전체 문제 중에서 사용자가 제출한 contest에 속한 문제를 필터링합니다.
    for prob in all_problems:
        contest_id = prob.get("contestId")
        if contest_id is None or contest_id not in contest_submitted:
            continue
        prob_key = (contest_id, prob.get("index"))
        # 세 명 중 한 명이라도 맞춘 경우 건너뜁니다.
        solved_by_any = any(prob_key in solved[handle] for handle in handles)
        if not solved_by_any:
            unsolved_problems.append(prob)
    
    # (중복 제거) 같은 문제가 중복해서 포함되었을 수 있으므로 (contestId, index)를 기준으로 중복 제거
    unique = {}
    for prob in unsolved_problems:
        key = (prob.get('contestId'), prob.get('index'))
        if key not in unique:
            unique[key] = prob
    unsolved_problems = list(unique.values())
    
    # 평점 정보가 있는 문제와 없는 문제로 분리 후 각각 정렬
    rated = [p for p in unsolved_problems if 'rating' in p]
    unrated = [p for p in unsolved_problems if 'rating' not in p]
    
    rated.sort(key=lambda p: p['rating'])
    unrated.sort(key=lambda p: (p.get('contestId', 0), p.get('index','')))
    
    sorted_problems = rated + unrated
    
    # 결과 출력: Contest ID, 문제 index, 문제 이름, 평점(있는 경우)
    print("\n세 명 모두가 풀지 않은 문제들:")
    for p in sorted_problems:
        contest_id = p.get('contestId')
        index = p.get('index')
        name = p.get('name')
        rating = p.get('rating', "Unrated")
        print(f"Contest {contest_id} {index}: {name} - Rating: {rating}")

if __name__ == '__main__':
    main()
