#pragma once
#include "../acl_cpp_define.hpp"
#include "stream_hook.hpp"

struct ACL_VSTREAM;

namespace acl {

class sslbase_conf;
class atomic_long;

class sslbase_io : public stream_hook
{
public:
	/**
	 * ���캯��
	 * @param conf {sslbase_conf&} ��ÿһ�� SSL ���ӽ������õ������
	 * @param server_side {bool} �Ƿ�Ϊ�����ģʽ����Ϊ�ͻ���ģʽ������
	 *  ģʽ�����ַ�����ͬ������ͨ���˲�������������
	 * @param nblock {bool} �Ƿ�Ϊ������ģʽ
	 */
	sslbase_io(sslbase_conf& conf, bool server_side, bool nblock = false);
	virtual ~sslbase_io(void);

	/**
	 * ssl ���ִ��鷽��
	 * @return {bool}
	 */
	virtual bool handshake(void) = 0;

	/**
	 * �����׽���Ϊ����ģʽ/������ģʽ
	 * @param yes {bool} ��Ϊ false ʱ����Ϊ����ģʽ��������Ϊ������ģʽ
	 */
	void set_non_blocking(bool yes);

	/**
	 * �жϵ�ǰ���õ� SSL IO �Ƿ�����ģʽ���Ƿ�����ģʽ
	 * @return {bool} ���� true ���ʾΪ������ģʽ������Ϊ����ģʽ
	 */
	bool is_non_blocking(void) const
	{
		return nblock_;
	}

	/**
	 * �ж� SSL �����Ƿ�ɹ�
	 * @return {bool}
	 */
	bool handshake_ok(void)
	{
		return handshake_ok_;
	}

protected:
	sslbase_conf& base_conf_;
	bool server_side_;
	bool nblock_;
	bool handshake_ok_;
	atomic_long* refers_;
	ACL_VSTREAM* stream_;
};

} // namespace acl