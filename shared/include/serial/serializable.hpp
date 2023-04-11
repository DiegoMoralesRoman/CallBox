#pragma once

namespace protouart::serial {
  class Serializable {
    public:
      virtual void serialize();
    private:
  };

}
