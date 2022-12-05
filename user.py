import abc

MEMBERSHIP = ["bronze", "gold"]
DEFAULT_POINT = 10000

class NotExistedIDError(Exception):
    def __init__(self):
        super.__init__('존재하지 않는 ID입니다.')


class User:
    def __init__(self, id):
        self.id = id
        self.membership = MEMBERSHIP[0]
        self.point = DEFAULT_POINT
        self.trade_cnt = 0

    def __repr__(self):
        return str(self.__dict__)


class UserDBInterface(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def __init__(self):
        """
        init
        """
        raise NotImplemented

    @abc.abstractmethod
    def addUser(self, id):
        """
        해당 id를 가지는 유저를 생성한다. ( 중복 검사 )
            param
                id: 유저의 id
            return
                True : 성공
                Fasle : 실패
        """
        raise NotImplemented

    @abc.abstractmethod
    def getInfo(self, id):
        """
        해당 id 를 가지는 유저 정보를 dict 형태로 반환합니다.
            param
                id 찾고자 하는 유저 id(PK)
            return
                유저 정보가 담긴 dictionary
        """
        raise NotImplemented

    @abc.abstractmethod
    def setPoint(self, id, newPoint):
        """
        해당 id 를 가지는 유저의 point 필드값을 newPoint로 수정합니다
            param
                id: 수정하고자 하는 유저의 id(PK)
                newPoint: point의 수정값
            return
                True: 성공
                False : 실패
        """
        raise NotImplemented

    @abc.abstractmethod
    def getAllInfo(self):
        """
        DB에 저장된 모든 User의 Info를 반환
            return
                모든 유저 정보가 담긴 list
        """
        raise NotImplemented

class MockUserDBImpl(UserDBInterface):
    def __init__(self):
        self.users = {}
        self.users['test'] = User('test')

    def addUser(self, id):
        if id in self.users: # id 중복
            return False
        else:
            self.users[id] = User(id)
            return True

    def getInfo(self, id):
        if id in self.users:
            return self.users[id].__dict__
        else:
            raise NotExistedIDError
        
        # return {
        #     "id": id,
        #     "membership": "bronze",
        #     "point": 10000,
        #     "trade_cnt": 0
        # }

    def setPoint(self, id, newPoint):
        if id in self.users:
            self.users[id].point = newPoint
            return True
        else:
            # raise NotExistedIDError
            return False

    def getAllInfo(self):
        return list(self.users.values())


if __name__ == "__main__":
    userdb = MockUserDBImpl()
    test = userdb.getInfo('test')
    print(test)
    userdb.addUser('abcd')
    abcd = userdb.getInfo('abcd')
    print(abcd)
    print(userdb.getAllInfo())
    for user in userdb.getAllInfo():
        print(user)
    