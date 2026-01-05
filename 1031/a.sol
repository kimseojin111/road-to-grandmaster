pragma solidity ^0.8.19; // >=0.8.19 <0.9.0; 

contract StorageExample {
    uint256 public mynumber = 42; // Creates a mynumber() function that returns mynumber aka getter 
    string public myText = "Hello"; 
    bool public isActive = true; 
    address public owner; 
    uint256 private secret; // not accessible from other contract   
    uint256 internal shared; // visible to this contract or child contracts 
    // default is internal 
    uint public constant FOO = 42; // cannot be changed  usually CAPITALIZED, 변수와 string 만 가능 
}

contract MyContract {
    // immutable variable -> constructor 에서만 할당 가능 
    address public immutable dep; 
    int256 public f;
    bytes3 d = 0x333333;
    constructor() {
        dep = msg.sender; // immutable 은 오직 변수만 가능. string 은 불가능 
    }
}

// reference type 포인터랑 뭐 비슷한거다~ 
contract ref {
    string public str = "Hello world!"; 
    uint256[10] public d = [10,20,40]; // 뭐 대충 이런거? 포인터를 가리킨다. 
    mapping(address => uint256) public balances; // dict 같은거 map 
    // struct 도 reference type 이라고???? 
    struct Person {
        string name; 
        uint256 age; 
        address walletAddress; 
    }
    bytes public dp; // dynamic bytes array 
}

contract PointerExample {
    // State array in storage
    uint256[] public storageArray = [1, 2, 3];
    
    function manipulateArray() public {
        // This creates a pointer to the storage array
        uint256[] storage storageArrayPointer = storageArray;
        
        // This modifies the actual storage array through the pointer
        storageArrayPointer[0] = 100;
        
        // At this point, storageArray is now [100, 2, 3]
        
        // This creates a copy in memory, not a pointer to storage
        uint256[] memory memoryArray = storageArray;
        
        // This modifies only the memory copy, not the storage array
        memoryArray[1] = 200;

        uint256[] memory A = [1,2,3,4]; 
        uint256[] memory B = A; // 
        B[0] = 100; 
        // A 는 ? 
        // At this point, storageArray is still [100, 2, 3]
        // and memoryArray is [100, 200, 3]
    }
}


contract Counter {
    uint256 public count = 0; 
    function increment() public {
        count = count + 1;   
    }
    function decrement() public {
        count = count - 1; 
    }
    function add(uint256 a, uint256 b) public pure returns (uint256) {
        // pure -> doesn't read or modify state 
        // public , private, internal, external     
        return a+b; 
    }
}