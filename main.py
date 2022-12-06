import abc
from user import UserDBImpl

class RentDBInterface(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def getInfo(self, uuid):
        """
        매개변수로 들어온, uuid 값을 가지는 Rent 정보를 전부 dictionary 형태로, 반환합니다. eg. {title: ..., description: ..., ...}
            param
                uuid: 정보를 가져 오고자 하는 대여 UUID
            return
                Rent 정보가 담긴 dict
        """
        raise NotImplemented

    @abc.abstractmethod
    def createRent(self, newRent):
        """
        매개변수로 들어온, newRent를 DB상에 등록합니다
            param
                newRent: 새로운 대여의 정보를 가지고 있는 dictionary
            return
                True : 저장 성공
                False : 저장 실패
        """
        raise NotImplemented

    @abc.abstractmethod
    def setLender(self, uuid, newLender):
        """
        uuid 값을 PK로 하는 대여항목에 Lender 필드를 갱신합니다
            param
                uuid: 수정하고자 하는 Rent의 uuid
                newLender: 등록하고자 하는 유저의 id(PK)값
            return
                True : 성공
                False : 실패
        """
        raise NotImplemented

    @abc.abstractmethod
    def getRendList(self, Lender):
        """
        Lender 필드의 값이 Lender와 일치하는 모든 Rent 정보들을 리스트에 담아 반환합니다
            param
                Lender: 찾고자 하는 User id(PK)값
            return
                Rent 정보들의 리스트 [{}, {}, ...]
        """
        raise NotImplemented

class MockRentDBImpl(RentDBInterface):
    def getInfo(self, uuid):
        return {
            "UUID": uuid,
            "title": "title",
            "description": "lorem ipsum",
            "deposit": 1000,
            "daily_rent_fee": 100,
            "lender": None,
        }

    def createRent(self, newRent):
        return True

    def setLender(self, uuid, newLender):
        return True

    def getRendList(self, Lender):
        return [{
            "UUID": 0,
            "title": "title",
            "description": "lorem ipsum",
            "deposit": 1000,
            "daily_rent_fee": 100,
            "lender": Lender,
        }, {
            "UUID": 1,
            "title": "title 2",
            "description": "lorem ipsum",
            "deposit": 2000,
            "daily_rent_fee": 200,
            "lender": Lender,
        }]

if __name__ == "__main__":
    userDB = UserDBImpl()

