#pragma once

#define MUST_USE_VALUE_ATTR [[nodiscard("You called a getter but did not use the returned value!")]]