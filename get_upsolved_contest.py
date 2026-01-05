import requests

def get_user_contests(handle):
    """
    주어진 핸들의 제출 기록에서 참여한 대회 ID들을 집합으로 반환합니다.
    """
    url = f"https://codeforces.com/api/user.status?handle={handle}"
    res = requests.get(url)
    data = res.json()
    
    if data['status'] != 'OK':
        print(f"Error fetching submissions for {handle}")
        return set()
    
    contests = set()
    for submission in data['result']:
        # 'contestId'가 없는 경우가 있을 수 있으므로 안전하게 처리합니다.
        if 'contestId' in submission:
            contests.add(submission['contestId'])
    
    return contests

def get_filtered_contests():
    """
    CodeForces의 contest.list API를 통해 대회 목록을 조회하고,
    대회 이름에 "Div. 1", "CodeTON", "Global", "VK" 중 하나라도 포함된 대회만 필터링하여 반환합니다.
    또한 'FINISHED' 상태의 대회만 고려합니다.
    """
    url = "https://codeforces.com/api/contest.list"
    res = requests.get(url)
    data = res.json()
    
    if data['status'] != 'OK':
        print("Error fetching contest list")
        return []
    
    contests = []
    keywords = ["Div. 1", "CodeTON", "Global", "VK", "Good", "Hello","Refact", "think-cell"]
    for contest in data['result']:
        # FINISHED 상태의 대회만 사용
        if contest['phase'] != 'FINISHED':
            continue
        
        # 대회 이름이 위 키워드 중 하나라도 포함하는지 검사합니다.
        if any(keyword in contest['name'] for keyword in keywords):
            contests.append(contest)
    
    # 대회 ID 기준 정렬(원하는 기준으로 정렬 가능)
    contests.sort(key=lambda x: x['id'])
    return contests

def main(handles):
    # 각 핸들의 참여한 대회 ID를 저장할 딕셔너리
    handle_contests = {}
    for handle in handles:
        print(f"{handle} 의 제출 정보를 불러오는 중...")
        handle_contests[handle] = get_user_contests(handle)
    
    print("필터 조건에 맞는 대회 정보를 불러오는 중...")
    filtered_contests = get_filtered_contests()

    # 모든 입력된 핸들이 제출 기록이 없는 대회 필터링
    no_submission_contests = []
    for contest in filtered_contests:
        contest_id = contest['id']
        # 모든 핸들에 대해 contest_id가 제출 집합에 없는 경우
        if all(contest_id not in handle_contests[handle] for handle in handles):
            no_submission_contests.append(contest)
    
    # 결과 출력
    if not no_submission_contests:
        print("모든 입력된 핸들이 제출 기록이 없는 필터 조건에 맞는 대회가 없습니다.")
    else:
        print("모든 입력된 핸들에 대해 제출 기록이 없는 대회:")
        for contest in no_submission_contests:
            print(f"{contest['id']}: {contest['name']}")

if __name__ == "__main__":
    # 사용자로부터 CodeForces 핸들을 공백으로 구분하여 입력받습니다.
    input_handles = ['JinyeongAckerman','gs25','ZmkzOWYyOHcwdWo4cj']
    main(input_handles)
