/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891
*/


#include "MGServer.h"
#include <iostream>
#include "gtest/gtest.h"
#include "ServerConf.h"
#include "RedisHandle.h"
#include "DataBaseOp.h"


// Single test to discover
TEST(serverConf, serverInitial)
{
	// 加载服务器的配置
	EXPECT_TRUE(ServerConf::GetInstance().LoadServerConf());
	// redis 的初始化 
	EXPECT_TRUE(RedisHandle::GetInstance().Init());
	// DataBase 的初始化 
	EXPECT_TRUE(DataBaseOp::GetInstance().Init());
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from %s\n", __FILE__);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// 如果正式运行，需要用下面的代码
// int  main(int argc, char ** argv) {
// 
// 	MGServer acceptServer;
// 
// 	acceptServer.StartServer();
// 
// 	return 0;
// 
// }
