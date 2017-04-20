/*
  Разбиение системы на компоненты позволяет снизить
  ее сложность. Ослабить связи между компонентами системы
  можно с помощью паттерна Facade. Объект Facade
  предоставляет единый упрощенный интерфейс к компонентам
  системы.
 */

#include <iostream>

using namespace std;

class MisDepartment {
public:
    void submitNetworkRequest() {
        this->state = 0;
    }

    bool checkOnStatus() {
        this->state++;
        if (this->state == Complete)
            return true;
        return false;
    }

private:
    enum States {
        Received, DenyAllKnowledge, ReferClientToFacilities,
        FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
        ElectricianDidItWrong, DispatchTechnician, SignedOff,
        DoesNotWork, FixElectriciansWiring, Complete
    };
    int state;
};

class ElectricianUnion {
public:
    void submitNetworkRequest() {
        this->state = 0;
    }

    bool checkOnStatus() {
        this->state++;
        if (this->state == Complete)
            return true;
        return false;
    }

private:
    enum States
    {
        Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
        WaitForAuthorization, DoTheWrongJob, BlameTheEngineer,
        WaitToPunchOut, DoHalfAJob, ComplainToEngineer,
        GetClarification, CompleteTheJob, TurnInThePaperwork,
        Complete
    };
    int state;
};

class FacilitiesDepartment {
public:
    void submitNetworkRequest() {
        this->state = 0;
    }

    bool checkOnStatus() {
        this->state++;
        if (this->state == Complete)
            return true;
        return false;
    }

private:
    enum States
    {
        Received, AssignToEngineer, EngineerResearches,
        RequestIsNotPossible, EngineerLeavesCompany,
        AssignToNewEngineer, NewEngineerResearches,
        ReassignEngineer,EngineerReturns,
        EngineerResearchesAgain, EngineerFillsOutPaperWork,
        Complete
    };
    int state;
};

class FacilitiesFacade
{
  public:
    FacilitiesFacade()
    {
        _count = 0;
    }
    void submitNetworkRequest()
    {
        _state = 0;
    }
    bool checkOnStatus()
    {
        _count++;
        /* Запрос на обслуживание получен */
        if (_state == Received)
        {
            _state++;
            /* Перенаправим запрос инженеру */
            _engineer.submitNetworkRequest();
            cout << "submitted to Facilities - " << _count
                 << " phone calls so far" << endl;
        }
        else if (_state == SubmitToEngineer)
        {
            /* Если инженер свою работу выполнил,
               перенаправим запрос электрику */
            if (_engineer.checkOnStatus())
            {
                _state++;
                _electrician.submitNetworkRequest();
                cout << "submitted to Electrician - " << _count
                     << " phone calls so far" << endl;
            }
        }
        else if (_state == SubmitToElectrician)
        {
            /* Если электрик свою работу выполнил,
               перенаправим запрос технику */
            if (_electrician.checkOnStatus())
            {
                _state++;
                _technician.submitNetworkRequest();
                cout << "submitted to MIS - " << _count
                     << " phone calls so far" << endl;
            }
        }
        else if (_state == SubmitToTechnician)
        {
            /* Если техник свою работу выполнил,
               то запрос обслужен до конца */
            if (_technician.checkOnStatus())
              return 1;
        }
        /* Запрос еще не обслужен до конца */
        return 0;
    }
    int getNumberOfCalls()

    {
        return _count;
    }
  private:
    enum States
    {
        Received, SubmitToEngineer, SubmitToElectrician,
        SubmitToTechnician
    };
    int _state;
    int _count;
    FacilitiesDepartment _engineer;
    ElectricianUnion _electrician;
    MisDepartment _technician;
};

int main() {
    FacilitiesFacade facilities;

    facilities.submitNetworkRequest();
    /* Звоним, пока работа не выполнена полностью */
    while (!facilities.checkOnStatus())
        ;
    cout << "job completed after only "
         << facilities.getNumberOfCalls()
         << " phone calls" << endl;

    return 0;
}
