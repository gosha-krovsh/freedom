#include "quest.h"

Quest::Quest(int id, const QString& name,
    const std::vector<std::shared_ptr<AbstractQuestNode>>& quest_nodes) :
    id_(id), name_(name), quest_nodes_(quest_nodes) {}
